#pragma once
#include <iostream>
#include "MyVector.hpp"
#include "User.h"
#include "Course.h"
#include "Message.h"

class DataHandler
{
public:
	static void loadCourses(MyVector<Course>& courses);
	static void loadUsers(MyVector<User*>& users);
	static void loadMessages(MyVector<Message>& messages);
	static void loadAssignments(MyVector<Assignment>& assignments);
	static void loadSubmissions(MyVector<Submission>& submissions, const MyVector<User*>& users);

	static void saveCourses(const MyVector<Course>& courses);
	static void saveUsers(const MyVector<User*>& users);
	static void saveMessages(const MyVector<Message>& messages);
	static void saveAssignments(const MyVector<Assignment>& assignments);
	static void saveSubmissions(const MyVector<Submission>& submissions);
};