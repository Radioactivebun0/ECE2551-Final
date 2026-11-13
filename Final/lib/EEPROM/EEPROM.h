#ifndef EEPROM_H
#define EEPROM_H

#include <Arduino.h>
#include <avr/io.h>

class EEPROM{
  public:
    EEPROM() {}

    static uint8_t Read(uint16_t address) {
      // Wait for EEPROM to finish, EEPE = 1 : Write in progress
      while (EECR & (1 << EEPE))
        ;

      // EEAR : address to read the data to
      EEAR = address;

      // Set EERE, triggers the read : Read Enable
      EECR |= (1 << EERE);

      // Read data from EEDR and return it. Where data is stored after a read.
      return EEDR;
    }

    // Range from 0-1023 addresses
    static void Write(uint16_t address, uint8_t data) {
      // Wait for EEPROM to finish, EEPE = 1 : Write in progress
      while (EECR & (1 << EEPE))
        ;

      // EEAR : address to write the data to
      EEAR = address;

      // EEDR : Data to be written
      EEDR = data;

      // Master Write Enable. "Arms the write", cleared after 4 clock cycles
      EECR |= (1 << EEMPE);

      // Write Enable. Only works if Master Write Enable is set. Actually sends the data.
      EECR |= (1 << EEPE);
    }
};

#endif