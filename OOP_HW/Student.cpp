#include "Student.h"

Student::Student(int id, const MyString& firstName, const MyString& lastName, const MyString& password)
	: User(id, firstName, lastName, password) 
{
	this->role = UserRole::Student;
}

User* Student::clone() const
{
	return new Student(*this);
}

const MyString& Student::getRoleString() const
{
	return "Student";
}
