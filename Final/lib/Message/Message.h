#ifndef MESSAGE_H
#define MESSAGE_H

#include <Arduino.h>
#include <string.h>

class Message{

    public:
    Message();
    Message(const uint8_t* from, const uint8_t* to, uint16_t payload, uint8_t length);
    Message(const uint8_t* from, uint8_t* to, const char* message);

    void setLength(uint8_t length){
        payloadLength = length;
    }

    void setTo(const uint8_t* to);
    void setFrom(const uint8_t* from);
    void setPayload(uint16_t p);

    uint8_t getLength() const{
        return payloadLength;
    }

    const uint8_t* getTo() const{
        return toUUID;
    }

    const uint8_t* getFrom() const{
        return fromUUID;
    }

    uint16_t getPayload() const{
        return payload;
    }

    char* getPayloadString() const;
    static uint16_t stringtoPayload(const char* message, uint8_t maxLen);
    static char* payloadtoString(uint16_t payload, uint8_t length);
    static uint8_t LENTHMSG(const char* input);

    static constexpr uint8_t UUID_LENGTH = 5;

    private:
    uint8_t toUUID[UUID_LENGTH];
    uint8_t fromUUID[UUID_LENGTH];
    uint16_t payload;
    uint8_t payloadLength;

};

#endif