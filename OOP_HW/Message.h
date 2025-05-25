#pragma once
#include "MyString.hpp"

class Message
{
private:
    int senderID;
    MyString content;
    MyString timestamp; 

    MyString getCurrentTime();

public:
    Message(int senderID, MyString content);
    const MyString& getContent() const;
    const MyString& getTimeStamp() const;
};

