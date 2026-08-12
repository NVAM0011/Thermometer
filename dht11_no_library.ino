// File:        dht11_no_library.ino
// Description: Reads humidity and temperature (Celsius) from a DHT11 sensor using 
//              1-wire serial communication protocol
// Author:      Isabella MacDonald
// Date:        Aug 10, 2026

// ---------------------------------------------------------------------
// Process Overview:
// 1. Host pulls the data line LOW for >= 18ms to say "wake up."
// 2. Host releases the line (goes back to INPUT_PULLUP).
// 3. Sensor responds: LOW 80us, then HIGH 80us (handshake).
// 4. Sensor sends 40 bits. Each bit = 50us LOW, then high pulse of two lengths:
//      bit 0: ~26-28us HIGH
//      bit 1: ~70us HIGH
// 5. The checksum is the sum of the first 4 bytes
// ---------------------------------------------------------------------

const uint8_t PIN_CHOICE = 2; // digital pin the DHT11 data line is on

// the DHT11 datasheet states that this is the minimum delay time between readings, in us
const unsigned long MIN_INTERVAL = 2000;

// how long to wait before we timeout and retry, in us
const unsigned long PULSE_TIMEOUT = 200;

// a pulse with duration longer than 40us reads as bit '1'
// a pulse with duration shorter than 40us reads as bit '0'
const unsigned long PULSE_THRESHOLD = 40;

// waits for the pin to reach a level, measuring how long we remain at that level
// timeout if it takes too long
long waitForPulse(uint8_t pin, uint8_t level, bool &timedOut) {
  unsigned long start = micros();
  while (digitalRead(pin) != level) {
    if (micros() - start > PULSE_TIMEOUT) {
      timedOut = true;
      return 0;
    }
  }
  // wait for the pin to reach the target level, or for timeout, whichever comes first
  unsigned long pulseStart = micros();
  while (digitalRead(pin) == level) {
    // calculate how long the pin stays at the level
    if (micros() - pulseStart > PULSE_TIMEOUT) {
      timedOut = true;
      return 0; // timed out
    }
  }
  timedOut = false;
  return micros() - pulseStart; // return the value from sensor
}

// handshakes and reads the 40 data bits into data[5].
// returns true if the handshake succeeded and the checksum matches.
bool readRawBits(uint8_t data[5]) {
  // resetting the bytes for the next reading
  data[0] = data[1] = data[2] = data[3] = data[4] = 0;
  bool timedOut;

  // 1. hold the line low for 18ms to wake up the sensor
  pinMode(PIN_CHOICE, OUTPUT);
  digitalWrite(PIN_CHOICE, LOW);
  delay(18); 
  pinMode(PIN_CHOICE, INPUT_PULLUP); // releasing the line
  delayMicroseconds(30); // pause for 30us before sensor takes control

  // 2. listen for the sensor to return the handshake, 80us LOW then 80us HIGH
  waitForPulse(PIN_CHOICE, LOW, timedOut);
  if (timedOut) return false; // sensor never pulled the line low
  waitForPulse(PIN_CHOICE, HIGH, timedOut);
  if (timedOut) return false; // sensor never released back to high

  // 3. get 40 data bits: each is a 50us LOW, then a HIGH that encodes the value.
  for (int i = 0; i < 40; i++) {
    waitForPulse(PIN_CHOICE, LOW, timedOut); // ignore this part
    if (timedOut) return false;

    long highDurationUs = waitForPulse(PIN_CHOICE, HIGH, timedOut); // measuring the value
    if (timedOut) return false;

    uint8_t byteIndex = i / 8; // put 8 bits into each byte
    data[byteIndex] <<= 1; // shift to add the next byte
    if (highDurationUs > (long)PULSE_THRESHOLD) {
      // if the pulse is long, we change the bit to 1 using bitwise OR
      // if the pulse is short the bitshift will set it to zero, so we do nothing
      data[byteIndex] |= 1; // long high pulse -> bit is 1
    }
    // short high pulse -> bit stays 0
  }

  // 4. Verify checksum: byte 4 should equal the sum of bytes 0-3.
  uint8_t checksum = (data[0] + data[1] + data[2] + data[3]) & 0xFF;
  return checksum == data[4];
}

// Performs a reading of the temperature in Celsius, and the humidity as a percentage.
// returns true if the temperature and humidity were successfully read.
  // DHT11 Serial Communication format:
  // byte 0 = humidity integer
  // byte 1 = humidity decimal
  // byte 2 = temperature integer
  // byte 3 = temperature decimal
  // byte 4 = checksum value
bool readDHT11(float &humidity, float &temperatureC) {
  // creating an empty byte to store what is sent by the sensor (5 bytes long)
  uint8_t data[5];
  if (!readRawBits(data)) {
    return false;
  }
  // adding together the integer and decimal components of the humidity value
  humidity = data[0] + data[1] * 0.1f;
  // adding together the integer and decimal components of the temperature value
  temperatureC = data[2] + data[3] * 0.1f;
  return true;
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 is now reading the temperature and humidity (no library)."));
  pinMode(PIN_CHOICE, INPUT_PULLUP);
}

void loop() {
  // delay between readings
  delay(MIN_INTERVAL);

  float humidity, temperature;
  bool read_ok = readDHT11(humidity, temperature);

  if (!read_ok) {
    Serial.println(F("DHT11 reading failed. Retrying..."));
    return;
  }

  Serial.print(("Temperature: "));
  Serial.print(temperature);
  Serial.print((" \u00b0C ")); // degrees celsius symbol
  Serial.print(("Humidity: "));
  Serial.print(humidity);
  Serial.println((" %"));
}
