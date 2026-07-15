//
// Created by Nico Macdonald on 2026-07-15.
//

#include "LCD.h"

int main()
{
    uint8_t rs = 1;
    uint8_t rw = 2;
    uint8_t en = 3;
    uint8_t data_pins[8] = {4,5,6,7,8,9,10,11};

    LCD my_lcd(rs, rw, en, data_pins);
    my_lcd.write("Hello World!");

    return 0;
}