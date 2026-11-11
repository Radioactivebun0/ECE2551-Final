#include "Message.h"
#include <Arduino.h>
#include <string.h>


Message::Message(){
    //Hint: use memset function
}

Message::Message(const uint8_t* from, const uint8_t* to, uint16_t payload, uint8_t length){

}

Message::Message(const uint8_t* from, uint8_t* to, const char* message){
  
}

void Message::setTo(const uint8_t* to){
     //Hint: use memcpy function
}

void Message::setFrom(const uint8_t* from){
        //Hint: use memcpy function
}

void Message::setPayload(uint16_t p){

}

char* Message::getPayloadString() const{

}

uint16_t Message::stringtoPayload(const char* message, uint8_t maxLen){
    
    }

  char* Message::payloadtoString(uint16_t payload, uint8_t length){
    
  }

uint8_t Message::LENTHMSG(const char* input){
    
}