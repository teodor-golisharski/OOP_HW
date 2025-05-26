#include "Submission.h"
#include "OutputMessages.h"

void Submission::checkGrade(double grade) const
{
	if (grade < 2 || grade > 6)
	{
		throw std::invalid_argument(ErrorMessages::INVALID_GRADE);
	}
}
void Submission::internalSetGrade(double grade)
{
	checkGrade(grade);
	this->grade = grade;
}

Submission::Submission(Student* student, const MyString& solution)
{
	if (!student)
	{
		throw std::invalid_argument(ErrorMessages::INVALID_STUDENT);
	}
	this->student = student;
	this->solution = solution;
}

int Submission::getStudentId() const
{
	return student->getId();
}
double Submission::getGrade() const
{
	return this->grade;
}
const MyString& Submission::getSolution() const
{
	return this->solution;
}

void Submission::setGrade(User* t, double grade)
{
	if (t->getRole() != UserRole::Teacher)
	{
		throw std::runtime_error(ErrorMessages::ACCESS_DENIED_TEACHER_REQUIREMENT);
	}
	internalSetGrade(grade);
}
