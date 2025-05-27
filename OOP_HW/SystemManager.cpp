#include "SystemManager.h"

void SystemManager::free()
{
	for (size_t i = 0; i < users.size(); i++)
	{
		delete users[i];
	}

	users.clear();
}

void SystemManager::loadAdmin()
{

}

SystemManager::SystemManager()
{
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
		std::cout << "- add_teacher <FirstName> <LastName> <password>\n"
			<< " - add_student <FirstName> <LastName> <password>\n"
			<< " - delete_user <id>\n"
			<< " - message_all <message>\n"
			<< " - mailbox\n"
			<< " - clear_mailbox\n"
			<< " - message <id> <message>\n";
	}
	else if (hasRole(UserRole::Teacher))
	{
		std::cout << "- change_password <old> <new>\n"
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
		std::cout << "- change_password <old> <new>\n"
			<< " - enroll <CourseName> <enrollmentPassword>\n"
			<< " - submit_assignment <CourseName> <AssignmentName> <solutionText>\n"
			<< " - grades\n"
			<< " - message <id> <message>\n"
			<< " - mailbox\n"
			<< " - clear_mailbox\n";
	}
}

void SystemManager::loadData()
{
	DataHandler::loadCourses(courses, users);
	DataHandler::loadAssignments(courses);
	DataHandler::loadUsers(users);
	DataHandler::loadSubmissions(courses);
	DataHandler::loadMessages(allMessages);
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

SystemManager::~SystemManager()
{
	saveData();
	free();
}
