#pragma once
#include "ApplicationConstants.h"

namespace ErrorMessages
{
	static const char* const INDEX_OUT_OF_RANGE = "Index out of range!";
	static const char* const NULL_POINTER = "Null pointer passed to MyString constructor.";
	static const char* const SUBSTR_OUT_OF_RANGE = "Substring out of range.";
	static const char* const FILE_NOT_FOUND = "Internal error. File is not found.";
	static const char* const LOADING_FAILED = "Loading information failed. Please contact support.";
	static const char* const SAVING_FAILED = "Saving information failed. Please contact support.";
	static const char* const FAILED_CREATING_USER = "User creation has failed. Please contact IT support.";				    

	static const char* const ACCESS_DENIED = "Access denied!";
	static const char* const ACCESS_DENIED_TEACHER_REQUIREMENT = "Access denied! Only teacher can grade submissions.";
	static const char* const INVALID_GRADE = "Grade must be from 2.00 to 6.00.";
	static const char* const INVALID_STUDENT = "Student is not present. Try again or contact support.";
	static const char* const EMPTY_ASSIGNMENT_TITLE = "Assignment title is empty.";
	static const char* const GENERAL_ERROR = "Error occured. Please try again.";
	static const char* const NO_LOGGED_USER = "There is no logged user.";
	static const char* const USER_NOT_FOUND = "User not found.";
	static const char* const USER_LOGGED_IN = "User is already logged in.";
	static const char* const INVALID_PASSWORD = "Invalid password!";
	static const char* const UNSUCCESSFUL_LOGIN = "Unsuccessful login. Please check your credentials and try again.";
	static const char* const NOT_LOGGED_IN = "Please login to use the application.";
	static const char* const WRONG_PASSWORD = "Wrong password!";
	static const char* const COURSE_EXISTS = "Course already exists.";
	static const char* const COURSE_NOT_FOUND = "Course not found.";
	static const char* const ASSIGNMENT_NOT_FOUND = "Assignment not found.";
	static const char* const ONLY_STUDENTS = "Only students can be added to the course.";
}

namespace InformativeMessages
{
	static const char* const NAMING_RULES = "Name must be at least 2 symbols and cannot contains certain special symbols.";
	static const char* const PASSWORD_RULES = "Password cannot contains certain special symbols.";
	static const char* const EMPTY_MAILBOX = "No messages to show!";
	static const char* const NO_SUBMISSIONS = "No submissions to this assignment.";
	static const char* const NOT_GRADED = "Not graded yet.";
}

namespace SuccessMessages
{
	static const char* const LOGIN_SUCCESSFUL = "Login successful!";
	static const char* const PASSWORD_CHANGE = "Password changed successfully!";
	static const char* const NEW_ASSIGNMENT = "Successfully created a new assignment!";

}