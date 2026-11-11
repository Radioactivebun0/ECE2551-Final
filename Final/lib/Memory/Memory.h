#ifndef MEMORY_H
#define MEMORY_H

#include <Arduino.h>
#include "Contact.h"
#include "Message.h"
#include <string.h>

class Memory{
    public:
    bool hasSchema();
    void setSchema();
    void clearMessages();
    void clearContacts();
    unsigned short getMessagePointerOffset();
    Memory();
    Memory(Contact node);
    unsigned char* getNodeUUID();
    char* getNodeName();
    unsigned short getNumberContacts();
    unsigned short getNumberMessages();
    Contact getContact(unsigned short index);
    Message getMessage(unsigned short index);
    bool saveContact(Contact contact);
    bool saveMessage(Message message);
    void saveNodeInformation(Contact contact);

    private:
    const unsigned short MAX_CONTACTS = 10;
    const unsigned short MAX_MESSAGES = 20;
};

#endif
