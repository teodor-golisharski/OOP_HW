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
    return loggedUser != nullptr;
}

void SystemManager::login(int id, const MyString& password)
{
}

void SystemManager::logout()
{
}

bool SystemManager::exit()
{
	return false;
}

void SystemManager::help()
{
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
    return loggedUser->getRole() == requiredRole;
}

SystemManager::~SystemManager()
{
	saveData();
	free();
}
