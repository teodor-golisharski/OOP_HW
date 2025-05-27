#pragma once
#include "MyString.hpp"
#include "MyVector.hpp"
#include "Submission.h"

class Assignment
{
	int id;
	int courseId;
	MyString title;
	MyVector<Submission> submissions;

	const MyVector<Submission>& getSubmissions() const;

	friend class DataHandler;
public:
	Assignment();
	Assignment(int id, int courseID, const MyString& title);

	int getId() const;
	int getCourseID() const;
	const MyString& getTtile() const;

	Submission& findSubmission(int studentId);
	void addSubmission(const Submission& sub);
};

