//
// Created by Nico MacDonald on 2026-07-03.
//

#include "LCD.h"
#include "Arduino.h"
/*
std::string message_sent_string = "Sent message to LCD: ";
std::string message_failed_string = "Failed to send message to LCD: ";
*/


LCD::LCD(uint8_t rs, uint8_t en, uint8_t dataPin, uint8_t clockPin, uint8_t latchPin)
{
    uint8_t m_rs = rs;
    uint8_t m_en = en;
    uint8_t m_dataPin = dataPin;
    uint8_t m_clockPin = clockPin;
    uint8_t m_latchPin = latchPin;
    //print_initialization_message();
}


void LCD::updateShiftRegister(byte data_value)
{
   digitalWrite(m_latchPin, LOW);
   shiftOut(m_dataPin, m_clockPin, LSBFIRST, data_value);
   digitalWrite(m_latchPin, HIGH);
}

void LCD::SetPins(bool rs_value, bool rw_value, bool en_value, byte data_value)
{
    digitalWrite(m_rs, rs_value);
    digitalWrite(m_en, en_value);
    updateShiftRegister(data_value);
}
