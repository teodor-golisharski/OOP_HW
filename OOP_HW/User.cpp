#include "User.h"


User::User(int id, const MyString& firstName, const MyString& lastName, const MyString& password)
{
	this->id = id;
	this->firstName = firstName;
	this->lastName = lastName;
	this->password = password;
	this->role = UserRole::Default;
}

int User::getId() const
{
	return this->id;
}

const MyString& User::getFirstName() const
{
	return this->firstName;
}

const MyString& User::getLastName() const
{
	return this->lastName;
}

const MyString& User::getPassword() const
{
	return this->password;
}

UserRole User::getRole() const
{
	return this->role;
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
