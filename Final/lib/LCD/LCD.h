#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include "LiquidCrystal.h"
typedef enum {Select, Left, Bottom, Top, Right, None} Buttons;




 class Button {
        public:

        Button(unsigned short pin, button_press pressbutton){
            
            }

            void hasbeenPushed(){
                
    };
    private:
   
};

class LCDKeypad : public LiquidCrystal, public Button {
    public:
    
    }
    };
#endif 