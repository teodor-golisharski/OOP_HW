#pragma once
#include "Student.h"
#include "DataHandler.h"

class Submission
{
	Student* student;
	MyString solution;
	double grade;

	void checkGrade(double grade) const;
	void internalSetGrade(double grade);

	friend class DataHandler;

public:
	Submission(Student* student, const MyString& solution);
	int getStudentId() const;
	double getGrade() const;
	const MyString& getSolution() const; 
	
	void setGrade(User* t, double grade);

};

