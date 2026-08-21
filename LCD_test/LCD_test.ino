#include "LCD.h"

void setup() {
  const uint8_t clockPin = 5; // Controls the clock in the serial to parralel chip
  const uint8_t latchPin = 6; // Controls the latch in the serial to parralel chip
  const uint8_t dataPin = 9; // Serial data input for the serial to parralel chip
  const uint8_t enablePin = 12; // Enables/Disables the LCD output
  const uint8_t rPin = 13; // Select data or instruction register on LCD

  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(rPin, OUTPUT);

  //Temp message string
}

void loop() {
  // get temp
  // LCD.write(temp)
  // delay
}
