#pragma once
#include "User.h"
#include "Course.h"

class Student : public User
{
	MyVector<Course*> enrolledCourses;

public:
	virtual const UserRole getRole() const override;
	virtual User* clone() const override;
};

