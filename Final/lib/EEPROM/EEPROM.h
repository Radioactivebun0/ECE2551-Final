#ifndef EEPROM_H
#define EEPROM_H

#include <Arduino.h>
#include <avr/io.h>
#include <vector>

class EEPROM{
  public:
    EEPROM() {}

    static uint8_t read(uint16_t addr){ // Starting address and how many bytes to return 
      uint8_t low  = eepromRead(addr);
      uint8_t high = eepromRead(addr + 1);
      return (high << 8) | low;
    }

    static void write(uint16_t addr, uint8_t data){
      eepromWrite(addr,       data & 0xFF);   // low byte
      eepromWrite(addr + 1,   data >> 8);     // high byte
    }

  private:
    static uint8_t eepromRead(uint16_t address) {
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
    static void eepromWrite(uint16_t address, uint8_t data) {
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