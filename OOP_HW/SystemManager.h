// Teodor Golisharski 6MI0600367
#pragma once
#include "MyVector.hpp"
#include "MyString.hpp"
#include "OutputMessages.h"
#include "DataHandler.h"
#include "User.h"
#include "Course.h"
#include "Message.h"
#include "IdGenerator.h"

class SystemManager
{
private:
	MyVector<Course> courses;
	MyVector<User*> users;
	MyVector<Message> allMessages;

	User* currentUser = nullptr;

	IdGenerator idGen;


	void removeTeacherFromCourses(int id);
	void free();
	bool isCourseUnique(const MyString& name) const;
	Course* findCourse(const MyString& name) const;
	User* findUser(int id) const;
public:
	SystemManager();
	bool isLoggedIn() const;

	void login(int id, const MyString& password);
	void logout();
	void exit();

	void deleteUser(int userId);
	void addUser(UserRole role, const MyString& firstName, const MyString& lastName, const MyString& password);
	void sendMessage(int recipientId, const MyString& content);
	void messageAll(const MyString& content);
	void changePassword(const MyString& oldPassword, const MyString& newPassword);
	void createCourse(const MyString& courseName, const MyString& pass);
	void addToCourse(const MyString& courseName, int studentId);
	void mailbox() const;
	void enroll(const MyString& courseName, const MyString& password);
	void assignHomework(const MyString& courseName, const MyString& assignmentName);
	void messageStudents(const MyString& courseName, const MyString& content);
	void submitAssignment(const MyString& courseName, const MyString& assignmentName, const MyString& content);
	void viewAssignmentSubmissions(const MyString& courseName, const MyString& assignmentName);
	void gradeAssignment(const MyString& courseName, const MyString& assignmentName, int studentId, double grade, const MyString& comment);
	void grades() const;
	void clearMailbox();
	void viewMailBox(int userId) const;

	void help() const;
	void loadData();
	void saveData() const;

	bool hasRole(UserRole requiredRole) const;

	~SystemManager();
};

