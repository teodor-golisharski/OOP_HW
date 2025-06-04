// Teodor Golisharski 6MI0600367
#pragma once
#include "User.h"

class Student : public User
{
	MyVector<int> courseIds;

	friend class DataHandler;
public:
	bool hasCourseId(int courseId) const;
	void addId(int id);
	Student(int id, const MyString& firstName, const MyString& lastName, const MyString& password);
	virtual User* clone() const override;
	virtual const char* getRoleString() const override;
};

