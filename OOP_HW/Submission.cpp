#include "Submission.h"
#include "OutputMessages.h"
#include "Utilities.h"

void Submission::checkGrade(double grade) const
{
	if (grade < 2 || grade > 6)
	{
		throw std::invalid_argument(ErrorMessages::INVALID_GRADE);
	}
}
void Submission::setGrade(double grade)
{
	checkGrade(grade);
	this->grade = grade;
}

void Submission::setComment(const MyString& comment)
{
	if(!validateString(comment))
	{
		throw std::invalid_argument(InformativeMessages::NAMING_RULES);
	}
	this->comment = comment;
}

Submission::Submission() : studentId(-1), solution(""), assignmentId(-1), grade(0)
{
}

Submission::Submission(int studentId, const MyString& solution, int assignmentId)
{
	this->studentId = studentId;
	if (!validateString(solution))
	{
		throw std::invalid_argument(InformativeMessages::NAMING_RULES);
	}
	this->solution = solution;
	this->assignmentId = assignmentId;
	this->grade = 0;
}

int Submission::getStudentId() const
{
	return studentId;
}
double Submission::getGrade() const
{
	return this->grade;
}
const MyString& Submission::getSolution() const
{
	return this->solution;
}

int Submission::getAssignmentId() const
{
	return this->assignmentId;
}

