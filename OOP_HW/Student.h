#pragma once
#include "User.h"

class Student : public User
{
public:
	Student(int id, const MyString& firstName, const MyString& lastName, const MyString& password);
	virtual User* clone() const override;
	virtual const MyString& getRoleString() const override;
};

