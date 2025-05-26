#pragma once
#include "OutputMessages.h"
#include "User.h"
#include "MyVector.hpp";
#include "MyString.hpp";
#include "Course.h";
#include "User.h"
#include "Message.h"

class SystemManager
{
private:
	MyVector<Course> courses;
	MyVector<User*> users;
	MyVector<Message> allMessages;

	User* loggedUser = nullptr;

	void free();
	void loadAdmin();
public:
	SystemManager();
	bool isLoggedIn() const;

	void login(int id, const MyString& password);
	void logout();
	bool exit();

	void help();
	void loadData();
	void saveData();

	bool hasRole(UserRole requiredRole) const;

	~SystemManager();
};

