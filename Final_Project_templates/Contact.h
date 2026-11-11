#ifndef CONTACT_H
#define CONTACT_H

#include <Arduino.h>
#include <string.h>

class  Contact
{
private:
    uint8_t uuid[5];
    char name[10];

public:
     Contact();
     Contact(const uint8_t* givenUUID, const char* givenName);
     Contact(unsigned char* givenUUID, char givenName);
     void setUUID(const uint8_t* givenUUID);
     void setName(const char* givenName);
     const uint8_t* getUUID(){
        return uuid;
     };

    char* getName(){
        return name;
     }

     static constexpr uint8_t UUID_LEN = 5;
     static constexpr uint8_t NAME_LEN = 10;

};
#endif