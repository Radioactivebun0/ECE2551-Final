#include "Memory.h"
#include "EEPROM.h"
#include <Arduino.h>

EEPROM myEEPROM;

bool Memory::hasSchema(){
   
}

void Memory::setSchema(){
    
}

void Memory::clearContacts(){

}

void Memory::clearMessages(){
  
}

unsigned short Memory::getMessagePointerOffset(){
  
} 

Memory::Memory(){

}

Memory::Memory(Contact node){
    
}

void Memory::saveNodeInformation(Contact contact){

}

unsigned char* Memory::getNodeUUID(){

}

char* Memory::getNodeName(){

}

unsigned short Memory::getNumberContacts(){

}

unsigned short Memory::getNumberMessages(){

}

Contact Memory::getContact(unsigned short index){
    
}

Message Memory::getMessage(unsigned short index){
    

}

bool Memory::saveContact(Contact contact){
    
}

bool Memory::saveMessage(Message message){
    
}