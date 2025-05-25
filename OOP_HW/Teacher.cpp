#include "Teacher.h"

Teacher::Teacher(const MyString& firstName, const MyString& lastName, int id, const MyString& password) 
	: User(firstName, lastName, id, password)
{
}

void Teacher::createCourse(const MyString& courseName)
{
}

void Teacher::addAssignmentToCourse(const MyString& courseName, const Assignment& assignment)
{
}

void Teacher::gradeSubmission(Course* course, Student* student, const MyString& assignmentName, int grade)
{

}

const UserRole Teacher::getRole() const
{
    return UserRole::Teacher;
}

User* Teacher::clone() const
{
    return new Teacher(*this) ;
}
