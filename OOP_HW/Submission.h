#pragma once
#include "MyString.hpp"
#include "MyVector.hpp"

class Submission
{
	int studentId;
	MyString solution;
	double grade;
	int assignmentId;
	MyString comment;

	void checkGrade(double grade) const;
	void setGrade(double grade);
	void setComment(const MyString& comment);

	friend class DataHandler;
	friend class SystemManager;
public:
	Submission();
	Submission(int studentId, const MyString& solution, int assignmentId);

	int getStudentId() const;
	double getGrade() const;
	const MyString& getSolution() const; 
	int getAssignmentId() const;
};

