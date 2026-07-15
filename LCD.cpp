//
// Created by Nico MacDonald on 2026-07-03.
//

#include "LCD.h"
#include <iostream>
#include <string>

// Create class constructor, take in pins, and creates an LCD object

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
    std::cout << "RS: " << m_rw << std::endl;
    std::cout << "RW: " << m_rw << std::endl;
    std::cout << "EN: " << m_en << std::endl;
    std::cout << "DATA PINS: " << m_data_pins << std::endl;
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