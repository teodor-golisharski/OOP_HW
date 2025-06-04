// Teodor Golisharski 6MI0600367
#include "Student.h"

bool Student::hasCourseId(int courseId) const
{
	for (size_t i = 0; i < courseIds.size(); i++)
	{
		if (courseIds[i] == courseId)
		{
			return true;
		}
	}
	return false;
}

void Student::addId(int id)
{
	if (!hasCourseId(id))
	{
		courseIds.push(id);
	}
}

Student::Student(int id, const MyString& firstName, const MyString& lastName, const MyString& password)
	: User(id, firstName, lastName, password)
{
	this->role = UserRole::Student;
}

User* Student::clone() const
{
	return new Student(*this);
}

const char* Student::getRoleString() const
{
	return "Student";
}
