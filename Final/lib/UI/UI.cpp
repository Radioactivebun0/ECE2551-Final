#include "Contact.h"
#include "Buzzer.h"
#include "LCD.h"
#include "Memory.h"
#include "Message.h"
#include "UI.h"


using namespace std;

UIState state = SETUP;

void UI() {


    LCDKeypad lcd_keypad(8, 9, 4, 5, 6, 7);
    lcd_keypad.begin(2, 16);

    while (true) {
        switch(state) {
            case SETUP:
                //SETUP CODE
                break;
            case MENU: 
                //SETUP CODE
                break;
            case ABOUT_ME: // do this
                String name; 
                String uuid;

                //NEED TO ACQUIRE NAME AND UUID FROM MEMORY CLASS FUNCTIONS

                lcd_keypad.setCursor(0, 0);
                lcd_keypad.print("Name: ");
                lcd_keypad.setCursor(0, 6);
                lcd_keypad.print(name);
                lcd_keypad.setCursor(1, 0);
                lcd_keypad.print("UUID: ");
                lcd_keypad.setCursor(1, 6);
                lcd_keypad.print(uuid);
                while(lcd_keypad.getButtonPress() != UP) {
                    
                }
                state = MENU;
                break;
            case CONTACTS: //NICK
                //SETUP CODE
                break;
            case NEW_CONTACT: // do this
                //SETUP CODE
                break;
            case NEW_CONTACT_NAME:
                //SETUP CODE
                break;
            case NEW_CONTACT_UUID:
                //SETUP CODE
                break;
            case CONTACT_ADDED:
                //SETUP CODE
                break;
            case LIST_FULL:
                //SETUP CODE
                break;
            case MESSAGES: //NICK
                //SETUP CODE
                break;
            case MESSAGE_OPEN:
                //SETUP CODE
                break;
            case MESSAGE_NEW:
                //SETUP CODE
                break;
            case MESSAGE_SENT:
                //SETUP CODE
                break;
            case MESSAGE_FAILED:
                //SETUP CODE
                break;
            case MESSAGE_RECIEVED:
                //SETUP CODE
                break;
        }
    }

}