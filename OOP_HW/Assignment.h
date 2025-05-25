#pragma once
#include "MyString.hpp"
#include "MyVector.hpp"
#include "Submission.h"

class Assignment
{
	MyString title;
	MyVector<Submission> submissions;

public:
	Submission& findSubmission(int studentId);
};

