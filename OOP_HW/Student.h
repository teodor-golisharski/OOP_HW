#pragma once
#include "User.h"

class Student : public User
{
	MyVector<int> enrolledCoursesIds;

public:
	Student(int id, const MyString& firstName, const MyString& lastName, const MyString& password);
	virtual User* clone() const override;
};

