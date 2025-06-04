#pragma once
#include "MyString.hpp"
#include "MyVector.hpp"
// Teodor Golisharski 6MI0600367
#include "Submission.h"

class Assignment
{
	int id;
	int courseId;
	MyString title;
	MyVector<Submission> submissions;

	const MyVector<Submission>& getSubmissions() const;
	Submission* findSubmission(int studentId);
	bool hasSubmitted(int studentId) const;

	friend class SystemManager;
	friend class DataHandler;
public:
	Assignment();
	Assignment(int id, int courseID, const MyString& title);

	int getId() const;
	int getCourseID() const;
	const MyString& getTitle() const;

	void addSubmission(const Submission& sub);
};

