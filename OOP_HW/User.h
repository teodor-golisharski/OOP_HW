#pragma once
#include "MyString.hpp"
#include "MyVector.hpp"
#include "Message.h"

enum class UserRole
{
	Default = 0,
	Admin = 1,
	Student = 2,
	Teacher = 3
};

class User
{
	MyString firstName;
	MyString lastName;
	int id;

	MyString password;
	MyVector<Message*> messages;
public:
	User();
	User(const MyString& firstName, const MyString& lastName, int id, const MyString& password);
    virtual ~User() {}
    int getId() const;
    const MyString getFullName() const;

    void receiveMessage(const Message& msg);
    void clearMailBox();

    virtual const UserRole getRole() const = 0;
    virtual User* clone() const = 0;

	virtual ~User() = default;
};

