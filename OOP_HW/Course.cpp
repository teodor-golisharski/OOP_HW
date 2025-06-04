// Teodor Golisharski 6MI0600367
#include "Course.h"
#include "Utilities.h"

void Course::addAssignment(const Assignment& a)
{
	assignments.push(a);
}

void Course::addStudent(Student* user)
{
    students.push(user);
}

bool Course::hasStudent(int studentId) const
{
    for (size_t i = 0; i < students.size(); i++)
    {
        if (students[i]->getId() == studentId)
        {
            return true;
        }
    }
    return false;
}

Course::Course(int id, const MyString& name, Teacher* teacher, const MyString& enrollmentPassword)
{
    this->id = id;
    if (!validateName(name))
    {
        throw std::invalid_argument(InformativeMessages::NAMING_RULES);
    }
    this->name = name;
    this->teacher = teacher;
    if (!validateString(enrollmentPassword))
    {
        throw std::invalid_argument(InformativeMessages::PASSWORD_RULES);
    }
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

Assignment* Course::findAssignmentByName(const MyString& name)
{
    for (size_t i = 0; i < assignments.size(); ++i)
    {
        if (assignments[i].getTitle() == name)
            return &assignments[i];
    }
    return nullptr;
}

const MyVector<Assignment>& Course::getAssignments() const
{
	return assignments;
}
