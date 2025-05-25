#include "Student.h"

const UserRole Student::getRole() const
{
	return UserRole::Student;
}

User* Student::clone() const
{
	return new Student(*this);
}
