#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal.h>

// Exact enum required by the project specification (Page 4)
typedef enum {LEFT, RIGHT, UP, DOWN, SELECT, NONE} Button;

class LCDKeypad : public LiquidCrystal {
  public:
    // Constructor: accepts the 6 LCD pins to pass to LiquidCrystal
    LCDKeypad(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

    // Required public method to read and debounce button presses
    Button getButtonPress();

  private:
    // Private tracking variables for non-blocking debouncing
    Button _lastRawReading;
    Button _confirmedState;
    unsigned long _lastDebounceTime;

    // Private helper method to map the raw A0 analog reading to a Button enum
    Button readRawButton();
};

#endif
