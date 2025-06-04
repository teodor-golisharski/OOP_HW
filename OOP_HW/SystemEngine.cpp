// Teodor Golisharski 6MI0600367

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
				return;
			}
			else if (command == "help")
			{
				manager.help();
			}
			else if (!manager.isLoggedIn())
			{
				if (command == "login")
				{
					int id;
					MyString pass;

					std::cin >> id >> pass;
					manager.login(id, pass);
				}
				else
				{
					std::cout << InformativeMessages::INVALID_COMMAND << std::endl;
				}
			}
			else if (manager.isLoggedIn())
			{
				if (command == "logout")
				{
					manager.logout();
				}
				else if (manager.hasRole(UserRole::Admin))
				{
					if (command == "add_teacher")
					{
						MyString firstName, lastName, password;
						std::cin >> firstName >> lastName >> password;

						manager.addUser(UserRole::Teacher, firstName, lastName, password);
					}
					else if (command == "add_student")
					{
						MyString firstName, lastName, password;
						std::cin >> firstName >> lastName >> password;

						manager.addUser(UserRole::Student, firstName, lastName, password);
					}
					else if (command == "delete_user")
					{
						int id;
						std::cin >> id;

						manager.deleteUser(id);
					}
					else if (command == "message_all")
					{
						char buffer[GeneralConstants::BUFFER_SIZE];

						std::cin.ignore();
						std::cin.getline(buffer, GeneralConstants::BUFFER_SIZE);

						MyString message(buffer);

						manager.messageAll(message);
					}
					else if (command == "message")
					{
						int recipientId;
						char buffer[GeneralConstants::BUFFER_SIZE];

						std::cin >> recipientId;
						std::cin.ignore();

						std::cin.getline(buffer, GeneralConstants::BUFFER_SIZE);

						MyString message(buffer);

						manager.sendMessage(recipientId, message);
					}
					else if (command == "view_mailbox")
					{
						int userId;
						std::cin >> userId;

						manager.viewMailBox(userId);
					}
					else
					{
						std::cout << InformativeMessages::INVALID_COMMAND << std::endl;
					}
				}
				else if (manager.hasRole(UserRole::Student))
				{
					if (command == "enroll")
					{
						MyString courseName, password;
						std::cin >> courseName >> password;

						manager.enroll(courseName, password);
					}
					else if (command == "submit_assignment")
					{
						MyString courseName, assignment;
						char buffer[GeneralConstants::BUFFER_SIZE];
						std::cin >> courseName >> assignment;

						std::cin.ignore();
						std::cin.getline(buffer, GeneralConstants::BUFFER_SIZE);

						manager.submitAssignment(courseName, assignment, buffer);
					}
					else if (command == "message")
					{
						int recipientId;
						char buffer[GeneralConstants::BUFFER_SIZE];

						std::cin >> recipientId;
						std::cin.ignore();

						std::cin.getline(buffer, GeneralConstants::BUFFER_SIZE);

						MyString message(buffer);

						manager.sendMessage(recipientId, message);
					}
					else if (command == "change_password")
					{
						MyString oldPassword, newPassword;
						std::cin >> oldPassword >> newPassword;

						manager.changePassword(oldPassword, newPassword);
					}
					else if (command == "mailbox")
					{
						manager.mailbox();
					}
					else if (command == "grades")
					{
						manager.grades();
					}
					else if (command == "clear_mailbox")
					{
						manager.clearMailbox();
					}
					else
					{
						std::cout << InformativeMessages::INVALID_COMMAND << std::endl;
					}
				}
				else if (manager.hasRole(UserRole::Teacher))
				{
					if (command == "create_course")
					{
						MyString courseName, password;
						std::cin >> courseName >> password;

						manager.createCourse(courseName, password);
					}
					else if (command == "change_password")
					{
						MyString oldPassword, newPassword;
						std::cin >> oldPassword >> newPassword;

						manager.changePassword(oldPassword, newPassword);
					}
					else if (command == "add_to_course")
					{
						MyString courseName;
						int studentId;
						std::cin >> courseName >> studentId;

						manager.addToCourse(courseName, studentId);
					}
					else if (command == "assign_homework")
					{
						MyString courseName, assignmentName;
						std::cin >> courseName >> assignmentName;

						manager.assignHomework(courseName, assignmentName);
					}
					else if (command == "grade_assignment")
					{
						char buffer[GeneralConstants::BUFFER_SIZE];

						MyString courseName, assignmentName;
						int studentId;
						double grade;

						std::cin >> courseName >> assignmentName >> studentId >> grade;

						std::cin.ignore();
						std::cin.getline(buffer, GeneralConstants::BUFFER_SIZE);

						manager.gradeAssignment(courseName, assignmentName, studentId, grade, buffer);
					}
					else if (command == "view_assignment_submissions")
					{
						MyString courseName, assignmentName;
						std::cin >> courseName >> assignmentName;

						manager.viewAssignmentSubmissions(courseName, assignmentName);
					}
					else if (command == "message_students")
					{
						MyString courseName;
						char buffer[GeneralConstants::BUFFER_SIZE];

						std::cin >> courseName;
						std::cin.ignore();
						std::cin.getline(buffer, GeneralConstants::BUFFER_SIZE);

						MyString message(buffer);
						manager.messageStudents(courseName, message);
					}
					else if (command == "mailbox")
					{
						manager.mailbox();
					}
					else if (command == "clear_mailbox")
					{
						manager.clearMailbox();
					}
					else
					{
						std::cout << InformativeMessages::INVALID_COMMAND << std::endl;
					}
				}
				else
				{
					std::cout << InformativeMessages::INVALID_COMMAND << std::endl;
				}
			}
			else
			{
				std::cout << InformativeMessages::INVALID_COMMAND << std::endl;
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
		std::cin.clear();
	}
}
