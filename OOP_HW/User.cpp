#include "User.h"

void User::changePassword(const MyString& oldPass, const MyString& newPass)
{
	if (oldPass != password)
	{
		throw std::invalid_argument(ErrorMessages::WRONG_PASSWORD);
	}
	if (!validateString(password))
	{
		throw std::invalid_argument(InformativeMessages::PASSWORD_RULES);
	}

	this->password = newPass;
}

User::User(int id, const MyString& firstName, const MyString& lastName, const MyString& password)
{
	this->id = id;

	if (!validateName(firstName) || !validateName(lastName))
	{
		if (role != UserRole::Admin)
		{
			throw std::invalid_argument(InformativeMessages::NAMING_RULES);
		}
	}
	if (!validateString(password))
	{
		if (role != UserRole::Admin)
		{
			throw std::invalid_argument(InformativeMessages::PASSWORD_RULES);
		}
	}

	this->lastName = lastName;
	this->firstName = firstName;
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

const MyString& User::getRoleString() const
{
	return "Default";
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
