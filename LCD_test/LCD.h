//
// Created by Nico MacDonald on 2026-07-03.
//

#ifndef THERMOMETER_LCD_H
#define THERMOMETER_LCD_H
#include "Arduino.h"
class LCD
{
public:
    LCD::LCD(uint8_t rs, uint8_t en, uint8_t dataPin, uint8_t shiftPin, uint8_t latchPin);
    void LCD::SetPins(bool rs_value, bool rw_value, bool en_value, byte data_value);
private:
    void LCD::updateShiftRegister(byte data_value);
    uint8_t m_rs;
    uint8_t m_en;
    uint8_t m_dataPin;
    uint8_t m_clockPin;
    uint8_t m_latchPin;
};

#endif //THERMOMETER_LCD_H