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

public:
    LCD(uint8_t rs, uint8_t rw, uint8_t en, const uint8_t data_pins[8]);
    void print_initialization_message();
    void write(std::string_view message) const;
    void clear() const;
};

#endif //THERMOMETER_LCD_H