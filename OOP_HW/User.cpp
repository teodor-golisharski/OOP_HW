#include "User.h"

User::User() = default;

User::User(const MyString& firstName, const MyString& lastName, int id, const MyString& password)
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->id = id;
	this->password = password;
}

int User::getId() const
{
	return this->id;
}

const MyString User::getFullName() const
{
	return firstName + " " + lastName;
}

void User::receiveMessage(const Message& msg)
{
	// messages.push(msg);
}

void User::clearMailBox()
{
	for (size_t i = 0; i < messages.getCapacity(); i++)
	{
		messages[i]->deleteMessage();
	}
}
