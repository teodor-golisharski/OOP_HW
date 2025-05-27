#pragma once
#include "MyVector.hpp";
#include "MyString.hpp";
#include "OutputMessages.h"
#include "DataHandler.h"
#include "User.h"
#include "Course.h";
#include "Message.h"
#include "IdGenerator.h"

class SystemManager
{
private:
	MyVector<Course> courses;
	MyVector<User*> users;
	MyVector<Message> allMessages;

	User* currentUser = nullptr;

	IdGenerator idGen;

	void free();
	void loadAdmin();
public:
	SystemManager();
	bool isLoggedIn() const;

	void login(int id, const MyString& password);
	void logout();
	bool exit();

	void help() const;
	void loadData();
	void saveData() const;

	bool hasRole(UserRole requiredRole) const;

	~SystemManager();
};

