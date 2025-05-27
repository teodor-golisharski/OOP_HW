#include "Course.h"

void Course::addAssignment(const Assignment& a)
{
	assignments.push(a);
}

Course::Course()
{
}

Course::Course(int id, const MyString& name, Teacher* teacher, const MyString& enrollmentPassword)
{
    this->id = id;
    this->name = name;
    this->teacher = teacher;
    this->enrollmentPassword = enrollmentPassword;
}


int Course::getId() const
{
    return this->id;
}

const MyString& Course::getName() const
{
    return this->name;
}

const MyString& Course::getEnrollmentPassword() const
{
    return this->enrollmentPassword;
}

Teacher* Course::getTeacher() const
{
    return teacher;
}

Assignment* Course::findAssignmentById(int id)
{
    for (size_t i = 0; i < assignments.size(); ++i)
    {
        if (assignments[i].getId() == id)
            return &assignments[i];
    }
    return nullptr;
}

const MyVector<Assignment>& Course::getAssignments() const
{
	return assignments;
}
