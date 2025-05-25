#pragma once
#include "MyString.hpp"
#include "MyVector.hpp"
#include "Message.h"

class User
{
	MyString firstName;
	MyString lastName;
	int id;

	MyString password;
	MyVector<Message> messages;
public:
    User(int id, MyString pass, MyString fName, MyString lName);
    virtual ~User() {}
    int getId() const;
    MyString getFullName() const;
    void receiveMessage(const Message& msg);
    void viewInbox();
    void deleteMessage(int index);

    virtual MyString getRole() const = 0;
};

