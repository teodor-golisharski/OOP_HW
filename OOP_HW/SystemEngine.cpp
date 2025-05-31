#include "SystemEngine.h"
#include "SystemManager.h"

void SystemEngine::run()
{
	SystemManager manager;
	manager.loadData();

	MyString command;
	while (true)
	{
		std::cout << "> ";
		std::cin >> command;
		try
		{
			if (command == "exit")
			{
				manager.exit();
			}
			else if (command == "help")
			{
				manager.help();
			}
			if (!manager.isLoggedIn())
			{
				if (command == "login")
				{
					int id;
					MyString pass;

					std::cin >> id >> pass;
					manager.login(id, pass);
				}
			}
			else if (manager.hasRole(UserRole::Admin))
			{

			}
			else if (manager.hasRole(UserRole::Student))
			{

			}
			else if (manager.hasRole(UserRole::Teacher))
			{

			}
		}
		catch (const std::invalid_argument& er)
		{
			std::cout << er.what() << std::endl;
		}
		catch (const std::runtime_error& er)
		{
			std::cout << er.what() << std::endl;
		}
		catch (const std::exception& er)
		{
			std::cout << er.what() << std::endl;
		}
	}
}
