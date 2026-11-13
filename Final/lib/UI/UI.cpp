#include "Contact.h"
#include "Buzzer.h"
#include "LCD.h"
#include "Memory.h"
#include "Message.h"
#include "UI.h"


using namespace std;

UIState state = SETUP;

void UI() {
    while (true) {
        switch(state) {
            case SETUP:
                //SETUP CODE
                break;
            case MENU:
                //SETUP CODE
                break;
            case ABOUT_ME:
                //SETUP CODE
                break;
            case CONTACTS:
                //SETUP CODE
                break;
            case NEW_CONTACT:
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
            case MESSAGES:
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