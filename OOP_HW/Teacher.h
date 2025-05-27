#pragma once
#include "User.h"
#include "MyString.hpp"
#include "MyVector.hpp"
#include "Assignment.h"

class Teacher : public User
{
private:
	MyVector<int> teachingCoursesIds;

public:
    Teacher(int id, const MyString& firstName, const MyString& lastName, const MyString& password);

    void createCourse(const MyString& courseName);
    void addAssignmentToCourse(const MyString& courseName, const Assignment& assignment);

    virtual User* clone() const override;
};

