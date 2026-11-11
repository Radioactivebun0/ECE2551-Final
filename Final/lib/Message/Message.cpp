#include "Message.h"
#include <Arduino.h>
#include <string.h>


Message::Message(){
  memset(toUUID, 0, sizeof(toUUID));
  memset(fromUUID, 0, sizeof(fromUUID));
  payload = 0;
  payloadLength = 0;
}

Message::Message(const uint8_t* from, const uint8_t* to, uint16_t payload, uint8_t length){
  setTo(to);
  setFrom(from);
  this->payload = payload;
  this->payloadLength = length;
}

Message::Message(const uint8_t* from, uint8_t* to, const char* message){
  setTo(to);
  setFrom(from);
  payloadLength = LENTHMSG(message); 
  payload = stringtoPayload(message, payloadLength);
}

void Message::setTo(const uint8_t* to){
  memcpy(toUUID, to, UUID_LENGTH);
}

void Message::setFrom(const uint8_t* from){
  memcpy(fromUUID, from, UUID_LENGTH);
}

void Message::setPayload(uint16_t p){
  payload = p;
}

char* Message::getPayloadString() const{
  return payloadtoString(payload, payloadLength);
}

uint16_t Message::stringtoPayload(const char* message, uint8_t maxLen){
    uint16_t result = 0;
    if (message == nullptr) return 0;
    if (maxLen > 2) maxLen = 2;

    memcpy(&result, message, maxLen);
    return result;
}

char* Message::payloadtoString(uint16_t payload, uint8_t length){
    static char mess[3];
    if (length > 2) length = 2;

    memcpy(mess, &payload, length);
    mess[length] = '\0';
    return mess;
}

uint8_t Message::LENTHMSG(const char* input){
  if(input == nullptr) return 0;
  size_t length = strlen(input);
  if (length > 2) return 2;
  else return length; 
}