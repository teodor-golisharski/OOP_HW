// Teodor Golisharski 6MI0600367
#pragma once
#include "MyString.hpp"
#include "MyVector.hpp"
#include "Message.h"
#include "Utilities.h"

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

	void changePassword(const MyString& oldPass, const MyString& pass);

	friend class SystemManager;
protected:
	UserRole role;

public:
	User(int id, const MyString& firstName, const MyString& lastName, const MyString& password);
	int getId() const;

	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const MyString& getPassword() const;

	void receiveMessage(const Message& msg);
	void clearMailBox();

	UserRole getRole() const;
	virtual const char* getRoleString() const;

	virtual User* clone() const = 0;

	virtual ~User() = default;
};

