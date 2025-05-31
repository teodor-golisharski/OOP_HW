#include "SystemManager.h"

void SystemManager::free()
{
	for (size_t i = 0; i < users.size(); i++)
	{
		delete users[i];
	}

	users.clear();
}
bool SystemManager::isCourseUnique(const MyString& name) const
{
	for (size_t i = 0; i < courses.size(); i++)
	{
		if (courses[i].getName() == name)
		{
			return false;
		}
	}
	return true;
}
Course* SystemManager::findCourse(const MyString& name) const
{
	for (size_t i = 0; i < courses.size(); i++)
	{
		if (courses[i].getName() == name)
		{
			return &courses[i];
		}
	}
	return nullptr;
}
User* SystemManager::findUser(int id) const
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getId() == id)
		{
			return users[i];
		}
	}
	return nullptr;
}
SystemManager::SystemManager()
{
}
SystemManager::~SystemManager()
{
	saveData();
	free();
}

void SystemManager::help() const
{
	std::cout << "Avaialbal commands:" << std::endl;
	if (!currentUser)
	{
		std::cout << " - login <id> <password>\n"
			<< " - exit\n";
		return;
	}
	std::cout << " - logout\n";
	std::cout << " - help\n";

	if (hasRole(UserRole::Admin))
	{
		std::cout << " - add_teacher <FirstName> <LastName> <password>\n"
			<< " - add_student <FirstName> <LastName> <password>\n"
			<< " - delete_user <id>\n"
			<< " - message_all <message>\n"
			<< " - mailbox\n"
			<< " - clear_mailbox\n"
			<< " - message <id> <message>\n";
	}
	else if (hasRole(UserRole::Teacher))
	{
		std::cout << " - change_password <old> <new>\n"
			<< " - create_course <CourseName> <enrollmentPassword>\n"
			<< " - add_to_course <CourseName> <studentID>\n"
			<< " - assign_homework <CourseName> <AssignmentName>\n"
			<< " - view_assignment_submissions <CourseName> <AssignmentName>\n"
			<< " - grade_assignment <CourseName> <AssignmentName> <studentID> <grade> <feedback>\n"
			<< " - message_students <CourseName> <message>\n"
			<< " - message <id> <message>\n"
			<< " - mailbox\n"
			<< " - clear_mailbox\n";
	}
	else if (hasRole(UserRole::Student))
	{
		std::cout << " - change_password <old> <new>\n"
			<< " - enroll <CourseName> <enrollmentPassword>\n"
			<< " - submit_assignment <CourseName> <AssignmentName> <solutionText>\n"
			<< " - grades\n"
			<< " - message <id> <message>\n"
			<< " - mailbox\n"
			<< " - clear_mailbox\n";
	}
}
bool SystemManager::isLoggedIn() const
{
	return currentUser != nullptr;
}
void SystemManager::login(int id, const MyString& password)
{
	if (isLoggedIn())
	{
		throw std::runtime_error(ErrorMessages::USER_LOGGED_IN);
	}

	for (unsigned i = 0; i < users.size(); i++)
	{
		if (users[i]->getId() == id)
		{

			if (users[i]->getPassword() != password)
			{
				throw std::invalid_argument(ErrorMessages::INVALID_PASSWORD);
			}
			currentUser = users[i];
			std::cout << SuccessMessages::LOGIN_SUCCESSFUL << std::endl;
			std::cout << currentUser->getFirstName() << " " << currentUser->getLastName() << " | " << currentUser->getRoleString() << " | " << currentUser->getId() << std::endl;
			return;
		}
	}
	throw std::runtime_error(ErrorMessages::UNSUCCESSFUL_LOGIN);
}
void SystemManager::logout()
{
	if (!isLoggedIn())
	{
		throw std::runtime_error(ErrorMessages::NOT_LOGGED_IN);
	}
	currentUser = nullptr;
}
bool SystemManager::exit()
{
	logout();
	saveData();
	free();
	return true;
}


void SystemManager::addUser(UserRole role, const MyString& firstName, const MyString& lastName, const MyString& password)
{
	User* user;
	switch (role)
	{
		case UserRole::Student: user = new Student(idGen.nextUser(), firstName, lastName, password);
		case UserRole::Teacher: user = new Teacher(idGen.nextUser(), firstName, lastName, password);

		default: throw std::runtime_error(ErrorMessages::FAILED_CREATING_USER);
	}
	sendMessage(currentUser->getId(), user->getId(), "Account created. Your password is: " + password);

	std::cout << "Added " << user->getRoleString() << " " << firstName << " " << lastName << " with ID " << user->getId() << "!" << std::endl;
}
void SystemManager::sendMessage(int senderId, int recipientId, const MyString& content)
{
	Message m(senderId, recipientId, content);
	allMessages.push(m);
}
void SystemManager::messageAll(const MyString& content)
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i])
		{
			sendMessage(currentUser->getId(), users[i]->getId(), content);
		}
	}
}

void SystemManager::changePassword(const MyString& oldPassword, const MyString& newPassword)
{
	currentUser->changePassword(oldPassword, newPassword);
	std::cout << SuccessMessages::PASSWORD_CHANGE << std::endl;
}
void SystemManager::createCourse(const MyString& courseName, const MyString& pass)
{
	if (!isCourseUnique(courseName))
	{
		throw std::invalid_argument(ErrorMessages::COURSE_EXISTS);
	}
	Teacher* t = dynamic_cast<Teacher*>(currentUser);
	Course course(idGen.nextCourse(), courseName, t, pass);
	courses.push(course);

}
void SystemManager::addToCourse(const MyString& courseName, int studentId)
{
	Course* tmp = findCourse(courseName);
	if (!tmp)
	{
		throw std::invalid_argument(ErrorMessages::COURSE_NOT_FOUND);
	}
	if (tmp->teacher->getId() != currentUser->getId())
	{
		throw std::runtime_error(ErrorMessages::ACCESS_DENIED);
	}

	User* tempUser = findUser(studentId);
	if (!tempUser)
	{
		throw std::invalid_argument(ErrorMessages::USER_NOT_FOUND);
	}
	if (tempUser->getRole() != UserRole::Student)
	{
		throw std::invalid_argument(ErrorMessages::ONLY_STUDENTS);
	}

	Student* s = dynamic_cast<Student*>(tempUser);
	tmp->addStudent(s);
}
void SystemManager::mailbox() const
{
	bool foundAny = false;
	for (size_t i = 0; i < allMessages.size(); i++)
	{
		if (allMessages[i].getRecipientID() == currentUser->getId() && !allMessages[i].getIsDeleted())
		{
			foundAny = true;
			int senderId = allMessages[i].getSenderID();
			User* sender = findUser(senderId);
			std::cout << "	" << allMessages[i].getTimeStamp() << ", sent by " << sender->getFirstName() << " " << sender->getLastName() << ": " << allMessages[i].getContent() << std::endl;
		}
	}
	if (!foundAny)
	{
		std::cout << "	" << InformativeMessages::EMPTY_MAILBOX << std::endl;
	}
}
void SystemManager::enroll(const MyString& courseName, const MyString& password)
{
	Course* tmp = findCourse(courseName);
	if (!tmp)
	{
		throw std::invalid_argument(ErrorMessages::COURSE_NOT_FOUND);
	}
	if (tmp->getEnrollmentPassword() != password)
	{
		throw std::invalid_argument(ErrorMessages::WRONG_PASSWORD);
	}
	tmp->addStudent(dynamic_cast<Student*>(currentUser));
	std::cout << "Successfully enrolled in " << tmp->getName() << "!" << std::endl;
}

void SystemManager::assignHomework(const MyString& courseName, const MyString& assignmentName)
{
	Course* tmp = findCourse(courseName);
	if (!tmp)
	{
		throw std::invalid_argument(ErrorMessages::COURSE_NOT_FOUND);
	}
	if (tmp->teacher->getId() != currentUser->getId())
	{
		throw std::runtime_error(ErrorMessages::ACCESS_DENIED);
	}

	Assignment as(idGen.nextAssignment(), tmp->getId(), assignmentName);
	tmp->addAssignment(as);

	std::cout << SuccessMessages::NEW_ASSIGNMENT << std::endl;
}
void SystemManager::messageStudents(const MyString& courseName, const MyString& content)
{
	Course* tmp = findCourse(courseName);
	if (!tmp)
	{
		throw std::invalid_argument(ErrorMessages::COURSE_NOT_FOUND);
	}
	if (tmp->teacher->getId() != currentUser->getId())
	{
		throw std::runtime_error(ErrorMessages::ACCESS_DENIED);
	}
	for (size_t i = 0; i < tmp->students.size(); i++)
	{
		sendMessage(currentUser->getId(), tmp->students[i]->getId(), content);
	}
}

void SystemManager::submitAssignment(const MyString& courseName, const MyString& assignmentName, const MyString& content)
{
	Course* tmp = findCourse(courseName);
	if (!tmp)
	{
		throw std::invalid_argument(ErrorMessages::COURSE_NOT_FOUND);
	}
	for (size_t i = 0; i < tmp->students.size(); i++)
	{
		if (tmp->students[i]->getId() == currentUser->getId())
		{
			Assignment* as = tmp->findAssignmentByName(assignmentName);
			if (!as)
			{
				throw std::invalid_argument(ErrorMessages::ASSIGNMENT_NOT_FOUND);
			}
			Submission sub(currentUser->getId(), content, as->getId());
			as->addSubmission(sub);
		}
	}
}
void SystemManager::viewAssignmentSubmissions(const MyString& courseName, const MyString& assignmentName)
{
	Course* tmp = findCourse(courseName);
	if (!tmp)
	{
		throw std::invalid_argument(ErrorMessages::COURSE_NOT_FOUND);
	}
	for (size_t i = 0; i < tmp->students.size(); i++)
	{
		if (tmp->students[i]->getId() == currentUser->getId())
		{
			Assignment* as = tmp->findAssignmentByName(assignmentName);
			if (!as)
			{
				throw std::invalid_argument(ErrorMessages::ASSIGNMENT_NOT_FOUND);
			}
			if (as->getSubmissions().size() == 0)
			{
				std::cout << InformativeMessages::NO_SUBMISSIONS << std::endl;
			}
			for (size_t i = 0; i < as->getSubmissions().size(); i++)
			{
				User* student = findUser(as->getSubmissions()[i].getStudentId());
				std::cout << "	" << student->getFirstName() << " " << student->getLastName() << ", " << student->getId() << ": " << as->getSubmissions()[i].getSolution();
				if (as->getSubmissions()[i].getGrade() != 0)
				{
					std::cout << "	Graded: " << as->getSubmissions()[i].getGrade() << std::endl;
				}
				else
				{
					std::cout << InformativeMessages::NOT_GRADED << std::endl;
				}
			}
		}
	}

}
void SystemManager::gradeAssignment(const MyString& courseName, const MyString& assignmentName, int studentId, double grade, const MyString& comment)
{
	Course* tmp = findCourse(courseName);
	if (!tmp)
	{
		throw std::invalid_argument(ErrorMessages::COURSE_NOT_FOUND);
	}
	for (size_t i = 0; i < tmp->students.size(); i++)
	{
		if (tmp->students[i]->getId() == currentUser->getId())
		{
			Assignment* as = tmp->findAssignmentByName(assignmentName);
			if (!as)
			{
				throw std::invalid_argument(ErrorMessages::ASSIGNMENT_NOT_FOUND);
			}
			as->findSubmission(studentId).setComment(comment);
			as->findSubmission(studentId).setGrade(grade);

			return;
		}
	}
}

void SystemManager::grades() const
{

}

void SystemManager::clearMailbox()
{
	for (size_t i = 0; i < allMessages.size(); i++)
	{
		if (allMessages[i].getRecipientID() == currentUser->getId())
		{
			allMessages[i].deleteMessage();
		}
	}
}




void SystemManager::loadData()
{
	DataHandler::loadMessages(allMessages);
	DataHandler::loadUsers(users);
	DataHandler::loadCourses(courses, users);
	DataHandler::loadAssignments(courses);
	DataHandler::loadSubmissions(courses);
}
void SystemManager::saveData() const
{
	DataHandler::saveUsers(users);
	DataHandler::saveCourses(courses);
	DataHandler::saveMessages(allMessages);
	DataHandler::saveAssignments(courses);
	DataHandler::saveSubmissions(courses);
}
bool SystemManager::hasRole(UserRole requiredRole) const
{
	return currentUser->getRole() == requiredRole;
}

