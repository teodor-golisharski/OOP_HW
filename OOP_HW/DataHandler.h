#pragma once
#include <iostream>
#include "MyVector.hpp"
#include "User.h"
#include "Course.h"
#include "Message.h"
#include "Admin.h"

class DataHandler
{
public:

	static void loadCourses(MyVector<Course>& courses, const MyVector<User*>& users);
	static void loadUsers(MyVector<User*>& users);
	static void loadMessages(MyVector<Message>& messages);
	static void loadAssignments(MyVector<Course>& courses);
	static void loadSubmissions(MyVector<Course>& courses);

	static void saveCourses(const MyVector<Course>& courses);
	static void saveUsers(const MyVector<User*>& users);
	static void saveMessages(const MyVector<Message>& messages);
	static void saveAssignments(const MyVector<Course>& courses);
	static void saveSubmissions(const MyVector<Course>& courses);
};