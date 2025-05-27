#pragma once
#include "MyString.hpp"
#include "MyVector.hpp"

class Submission
{
	int studentId;
	MyString solution;
	double grade;
	int assignmentId;

	void checkGrade(double grade) const;

	void setGrade(double grade);

	friend class DataHandler;

public:
	Submission();
	Submission(int studentId, const MyString& solution, int assignmentId);

	int getStudentId() const;
	double getGrade() const;
	const MyString& getSolution() const; 
	int getAssignmentId() const;
};

