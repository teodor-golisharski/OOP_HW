#pragma once
#include "User.h"
#include "Assignment.h"
#include "Course.h"
#include "MyString.hpp"
#include "MyVector.hpp"

class Teacher : public User
{
private:
	MyVector<Course*> teachingCourses;

public:
    Teacher(const MyString& firstName, const MyString& lastName, int id, const MyString& password);

    void createCourse(const MyString& courseName);
    void addAssignmentToCourse(const MyString& courseName, const Assignment& assignment);
    void gradeSubmission(Course* course, Student* student, const MyString& assignmentName, double grade);

    // const MyVector<Course*>& getTeachingCourses() const;

    virtual const UserRole getRole() const override;
    virtual User* clone() const override;
};

