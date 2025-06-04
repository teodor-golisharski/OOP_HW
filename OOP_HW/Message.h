// Teodor Golisharski 6MI0600367
#pragma once
#include "MyString.hpp"

class Message
{
private:
    int senderId;
    int recipientId;
    MyString content;
    MyString timestamp; 
    bool isDeleted;

    MyString getCurrentTime();
public:
    Message();
    Message(int senderID, int recipientID, const MyString& content);
    
    const MyString& getContent() const;
    const MyString& getTimeStamp() const;

    int getSenderID() const;
    int getRecipientID() const;
    bool getIsDeleted() const;

    void overrideTimestamp(const MyString& newTimestamp);
    void deleteMessage();
};

