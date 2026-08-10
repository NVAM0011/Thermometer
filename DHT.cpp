// File: dht.cpp
// Description: driver code to read humidity and temperature in Celsius using the DHT11 sensor library
// Author: Isabella MacDonald
// Date: Aug 10, 2026

// Install the following libraries:
// 1) DHT Sensor Library
// 2) Unified Sensor Library by Adafruit

// including the header file from the DHT sensor library
#include "DHT.h"

// Initialize DHT sensor using the desired pin and type of DHT thermometer
// here we are using the digital pin 2, and the thermometer is the version DHT11
DHT dht(2, DHT11);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 is now reading the temperature and humidity."));
  dht.begin();
}

void loop() {
  // delay between readings
  delay(4000);
  // get the humidity reading from DHT library as a percentage
  float humidity = dht.readHumidity();
  // get the temperature reading from DHT library as a float in degrees Celsius
  float temperature = dht.readTemperature(false);

  // error message for failed readings
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("DHT 11 reading failed."));
    return;
  }
  Serial.print(F("Temperature: "));
  Serial.print(temperature);
  Serial.print(F("°C "));
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.println("%");
}
