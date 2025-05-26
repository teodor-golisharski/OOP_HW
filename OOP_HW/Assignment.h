#pragma once
#include "MyString.hpp"
#include "MyVector.hpp"
#include "Submission.h"

class Assignment
{
	int courseID;
	MyString title;
	MyVector<Submission> submissions;

public:
	Assignment(int courseID, const MyString& title);
	Submission& findSubmission(int studentId);
};

