//
// Created by Nico MacDonald on 2026-07-03.
//

#ifndef THERMOMETER_LCD_H
#define THERMOMETER_LCD_H
#include <iostream>
class LCD
{
private:
    uint8_t m_rs = 0;
    uint8_t m_rw = 0;
    uint8_t m_en = 0;
    uint8_t m_data_pins[8] = { };
    int tDelayNanoSeconds = 100;
    int outputEnablePin = 1;      // (11) ST_CP [RCK] on 74HC595
    int latchClockPin = 2;      // (9) SH_CP [SCK] on 74HC595
    int dataPin = 9;     // (12) DS [S1] on 74HC595
    int shiftPin = 4;
    int resetPin = 5;

public:
    LCD(uint8_t rs, uint8_t rw, uint8_t en, const uint8_t data_pins[8]);
    void print_initialization_message();
    void write(std::string_view message) const;
    void clear() const;
    void shift_data_into_register();
    void reset_shift_register();
    void output_shift_register();
    void enable_output();
    void disable_output();
};

#endif //THERMOMETER_LCD_H