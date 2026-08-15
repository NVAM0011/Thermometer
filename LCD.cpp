//
// Created by Nico MacDonald on 2026-07-03.
//

#include "LCD.h"
#include <iostream>
#include <string>
// #include "Arduino.h"

std::string message_sent_string = "Sent message to LCD: ";
std::string message_failed_string = "Failed to send message to LCD: ";


LCD::LCD(uint8_t rs, uint8_t rw, uint8_t en, const uint8_t data_pins[8])
{
    m_rs = rs;
    m_rw = rw;
    m_en = en;
    for (uint8_t i = 0; i < 8; i++)
    {
        m_data_pins[i] = data_pins[i];
    }
    print_initialization_message();
}

void LCD::print_initialization_message()
{
    std::cout << "LCD initialized with the following pins:" << std::endl;
    std::cout << "RS: " << unsigned(m_rs) << std::endl;
    std::cout << "RW: " << unsigned(m_rw) << std::endl;
    std::cout << "EN: " << unsigned(m_en) << std::endl;
    std::cout << "DATA PINS: " << std::endl;
    for (unsigned char m_data_pin : m_data_pins)
    {
        std::cout << unsigned(m_data_pin) << std::endl;
    }
    std::cout << std::endl;
}

void LCD::write(const std::string_view message_string) const
{
    std::cout << message_sent_string << message_string << std::endl;
    std::cout << m_rw << std::endl;
}

void LCD::clear() const
{
    // Clear the LCD of text
}

uint8_t LCD_Pins = 0;

void LCD::shift_data_into_register(){
    pinMode(shiftPin, HIGH);
    shiftOut(dataPin, shiftPin, LSBFIRST, LCD_Pins);
    pinMode(shiftPin, LOW);
}

void LCD::reset_shift_register()
{
    digitalWriter(resetPin, LOW);
    delay(tDelayNanoSeconds);
    digitalWriter(resetPin, HIGH);

}

void LCD::output_shift_register()
{
    digitalWrite(outputEnablePin, HIGH);
}

void LCD::enable_output(){}

void LCD::disable_output(){}
