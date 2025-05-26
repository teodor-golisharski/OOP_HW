#pragma once
#include "MyString.hpp"

class Message
{
private:
    int senderID;
    int recipientID;
    MyString content;
    MyString timestamp; 
    bool isDeleted;

    MyString getCurrentTime();

public:
    Message(int senderID, int recipientID, const MyString& content);
    
    const MyString& getContent() const;
    const MyString& getTimeStamp() const;

    int getSenderID() const;
    int getRecipientID() const;
    bool getIsDeleted() const;

    void overrideTimestamp(const MyString& newTimestamp);
    void deleteMessage();
};

