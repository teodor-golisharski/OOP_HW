#include "Teacher.h"

Teacher::Teacher(int id, const MyString& firstName, const MyString& lastName, const MyString& password)
	: User(id, firstName, lastName, password)
{
	role = UserRole::Teacher;
}

void Teacher::createCourse(const MyString& courseName)
{

}

void Teacher::addAssignmentToCourse(const MyString& courseName, const Assignment& assignment)
{

}

User* Teacher::clone() const
{
	return new Teacher(*this);
}
