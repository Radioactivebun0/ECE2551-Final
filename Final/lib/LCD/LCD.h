#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal.h>
#include <Arduino.h>
#include "LiquidCrystal.h"


typedef enum {LEFT, RIGHT, UP, DOWN, SELECT, NONE} ButtonType;
typedef void (*button_press)(ButtonType);

class Button{
  public:
  Button(unsigned short pin, button_press pressbutton){
    _pin=pin;
    _callback = pressbutton;
    _lastButton =NONE;
    _lastChangeTime =0;
  }
  
  ButtonType getButtonPress(){
    int v= analogRead(A0);
    if(v <50){
      return RIGHT;
      
    }else if(v <250){
    return UP; 
         
    }else if(v <450){
    return DOWN; 
         
    }else if(v <650){
    return LEFT;
      
    }else if(v <250){
    return SELECT;
      
    }else{
    return NONE;
    } 
  }
  
  void updateButtonState(){
    ButtonType currentButton = getButtonPress();
    const unsigned long debounceDelay = 50;

    if(currentButton != _lastButton){
      _lastChangeTime = millis();
    }

    if((millis() - _lastChangeTime) > debounceDelay){
      if(currentButton != _lastButton){
        _lastButton = currentButton;
        if(_callback != NULL){
          _callback(_lastButton);
        }
      }
    }
    _lastButton = currentButton;
  }
    
  private:
  unsigned short _pin;
  button_press _callback;
  ButtonType _lastButton;
  unsigned long _lastChangeTime;
   
};

// helper function for which button was pressed
Button getButtonPress();
  

class LCDKeypad : public LiquidCrystal, public Button {
    public:
    
    }
    };
#endif 