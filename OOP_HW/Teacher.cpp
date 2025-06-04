// Teodor Golisharski 6MI0600367
#include "Teacher.h"

Teacher::Teacher(int id, const MyString& firstName, const MyString& lastName, const MyString& password)
	: User(id, firstName, lastName, password)
{
	role = UserRole::Teacher;
}

User* Teacher::clone() const
{
	return new Teacher(*this);
}

const char* Teacher::getRoleString() const
{
	return "Teacher";
}
