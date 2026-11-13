#include "LCD.h"

LCDKeypad::LCDKeypad(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
  : LiquidCrystal(rs, enable, d4, d5, d6, d7) {
    _lastRawReading = NONE;
    _confirmedState = NONE;
    _lastDebounceTime = 0;
}

Button LCDKeypad::readRawButton() {
    int v= analogRead(A0);

    if(v <50){
    return RIGHT;
      
    }else if(v <250){
    return UP; 
         
    }else if(v <450){
    return DOWN; 
         
    }else if(v <650){
    return LEFT;
      
    }else if(v <900){
    return SELECT;
      
    }else{
    return NONE;
    } 
  }

Button LCDKeypad::getButtonPress() { // call this function to get the current button press returns NONE if no button press
  Button currentButton = readRawButton();
  const unsigned long debounceDelay = 50;

  if(currentButton != _lastRawReading){
    _lastDebounceTime = millis();
    _lastRawReading = currentButton;
    }

    if((millis() - _lastDebounceTime) > debounceDelay){
      if(currentButton != _confirmedState){
        _confirmedState = currentButton;

        if(_confirmedState != NONE){
        return _confirmedState;
      }
      }
    }
    return NONE;
  }
