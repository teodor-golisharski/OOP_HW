// Teodor Golisharski 6MI0600367
#pragma once
#include <iostream>
#include <fstream>
#include "DataHandler.h"
#include "ApplicationConstants.h"

void DataHandler::loadCourses(MyVector<Course>& courses, const MyVector<User*>& users)
{
	std::ifstream in(FileNames::COURSES);
	if (!in.is_open()) return;

	char buffer[1024];
	while (in.getline(buffer, 1024))
	{
		MyString line(buffer);
		MyVector<MyString> tokens = line.split(GeneralConstants::DELIMETER);
		if (tokens.size() < 4) continue;

		int id = tokens[0].toInt();
		MyString name = tokens[1];
		MyString password = tokens[2];
		int teacherId = tokens[3].toInt();

		MyVector<Student*> fillStudents;

		Teacher* teacher = nullptr;
		for (size_t i = 0; i < users.size(); ++i)
		{
			if (users[i]->getId() == teacherId && users[i]->getRole() == UserRole::Teacher)
			{
				teacher = dynamic_cast<Teacher*>(users[i]);
			}
			else if (users[i]->getRole() == UserRole::Student)
			{
				Student* st = dynamic_cast<Student*>(users[i]);
				for (size_t j = 0; j < st->courseIds.size(); j++)
				{
					if (st->hasCourseId(id))
					{
						fillStudents.push(st);
					}
				}
			}
		}

		if (!teacher)
		{
			throw std::runtime_error(ErrorMessages::LOADING_FAILED);
		}

		Course course(id, name, teacher, password);

		for (size_t i = 0; i < fillStudents.size(); i++)
		{
			course.addStudent(fillStudents[i]);
		}

		courses.push(course);
	}

	in.close();
}
void DataHandler::loadUsers(MyVector<User*>& users)
{
	std::ifstream in(FileNames::USERS);
	bool adminExists = false;

	if (!in.is_open())
	{
		users.push(new Admin(0, "System", "Admin", "00000"));
		saveUsers(users);
		adminExists = true;
		return;
	}

	char buffer[1024];
	while (in.getline(buffer, 1024))
	{
		MyString line(buffer);
		MyVector<MyString> tokens = line.split(GeneralConstants::DELIMETER);
		if (tokens.size() < 5) continue;

		int id = tokens[0].toInt();
		MyString firstName = tokens[1];
		MyString lastName = tokens[2];
		MyString password = tokens[3];
		int roleInt = tokens[4].toInt();
		UserRole role = static_cast<UserRole>(roleInt);

		MyVector<int> ids;
		if (role == UserRole::Student)
		{
			MyString opt = tokens[5];
			if (opt.length() > 0)
			{
				for (size_t i = 0; i < opt.split(GeneralConstants::ID_SEPERATOR).size(); i++)
				{
					ids.push(opt.split(GeneralConstants::ID_SEPERATOR)[i].toInt());
				}
			}
		}

		User* user = nullptr;
		switch (role)
		{
			case UserRole::Student:
			{
				user = new Student(id, firstName, lastName, password);
				Student* st = dynamic_cast<Student*>(user);
				st->courseIds = ids;
				break;
			}
			case UserRole::Teacher:
				user = new Teacher(id, firstName, lastName, password);
				break;
			case UserRole::Admin:
				user = new Admin(id, firstName, lastName, password);
				adminExists = true;
				break;
			default:
				throw std::runtime_error(ErrorMessages::USER_NOT_FOUND);
		}

		users.push(user);
	}

	in.close();

	if (!adminExists)
	{
		users.push(new Admin(0, "System", "Admin", "00000"));
		saveUsers(users);
	}
}
void DataHandler::loadMessages(MyVector<Message>& messages)
{
	std::ifstream in(FileNames::MESSAGES);

	if (!in.is_open()) return;

	char buffer[1024];
	while (in.getline(buffer, 1024))
	{
		MyString line(buffer);
		MyVector<MyString> tokens = line.split(GeneralConstants::DELIMETER);

		if (tokens.size() < 5) continue;

		int senderID = tokens[0].toInt();
		int recipientID = tokens[1].toInt();
		MyString timestamp = tokens[2];
		bool isDeleted = (tokens[3] == "1");
		MyString content = tokens[4];

		Message msg(senderID, recipientID, content);
		msg.overrideTimestamp(timestamp);
		if (isDeleted) msg.deleteMessage();

		messages.push(msg);
	}
}
void DataHandler::loadAssignments(MyVector<Course>& courses)
{
	std::ifstream in(FileNames::ASSIGNMENTS);

	if (!in.is_open()) return;

	char buffer[1024];
	while (in.getline(buffer, 1024))
	{
		MyString line(buffer);
		MyVector<MyString> tokens = line.split(GeneralConstants::DELIMETER);

		if (tokens.size() < 3) continue;

		int id = tokens[0].toInt();
		int courseId = tokens[1].toInt();
		MyString title = tokens[2];

		Assignment a(id, courseId, title);
		for (size_t i = 0; i < courses.size(); i++)
		{
			if (courses[i].getId() == courseId)
			{
				courses[i].addAssignment(a);
			}
		}
	}
}
void DataHandler::loadSubmissions(MyVector<Course>& courses)
{
	std::ifstream in(FileNames::SUBMISSIONS);
	if (!in.is_open()) return;

	char buffer[1024];

	while (in.getline(buffer, 1024))
	{
		MyString line(buffer);
		MyVector<MyString> tokens = line.split(GeneralConstants::DELIMETER);
		if (tokens.size() < 5) continue;

		int assignmentId = tokens[0].toInt();
		int studentId = tokens[1].toInt();
		double grade = tokens[2].toDouble();
		MyString solution = tokens[3];
		MyString comment = tokens[4];

		Assignment* targetAssignment = nullptr;

		for (size_t i = 0; i < courses.size(); i++)
		{
			Assignment* found = courses[i].findAssignmentById(assignmentId);
			if (found)
			{
				targetAssignment = found;
				break;
			}
		}

		if (!targetAssignment)
		{
			throw std::runtime_error(ErrorMessages::LOADING_FAILED);
		}

		Submission sub(studentId, solution, assignmentId);
		sub.setGrade(grade);
		sub.setComment(comment);

		targetAssignment->addSubmission(sub);
	}
	in.close();
}


void DataHandler::saveCourses(const MyVector<Course>& courses)
{
	std::ofstream out(FileNames::COURSES, std::ios::trunc);
	if (!out.is_open())
	{
		throw std::runtime_error(ErrorMessages::FILE_NOT_FOUND);
	}

	for (size_t i = 0; i < courses.size(); i++)
	{
		out << courses[i].getId() << GeneralConstants::DELIMETER
			<< courses[i].getName() << GeneralConstants::DELIMETER
			<< courses[i].getEnrollmentPassword() << GeneralConstants::DELIMETER
			<< courses[i].getTeacher()->getId()
			<< '\n';
	}

	out.close();
}
void DataHandler::saveUsers(const MyVector<User*>& users)
{
	std::ofstream out(FileNames::USERS, std::ios::trunc);
	if (!out.is_open())
	{
		throw std::runtime_error(ErrorMessages::FILE_NOT_FOUND);
	}

	for (size_t i = 0; i < users.size(); i++)
	{
		User* user = users[i];
		out << user->getId() << GeneralConstants::DELIMETER
			<< user->getFirstName() << GeneralConstants::DELIMETER
			<< user->getLastName() << GeneralConstants::DELIMETER
			<< user->getPassword() << GeneralConstants::DELIMETER
			<< static_cast<int>(user->getRole());

		if (user->getRole() == UserRole::Student)
		{
			out << GeneralConstants::DELIMETER << GeneralConstants::ID_SEPERATOR;
			Student* st = dynamic_cast<Student*>(user);
			for (size_t j = 0; j < st->courseIds.size(); j++)
			{
				out << st->courseIds[j];
				if (j != st->courseIds.size() - 1)
				{
					out << GeneralConstants::ID_SEPERATOR;
				}
			}
		}
		out << "\n";
	}

	out.close();
}
void DataHandler::saveMessages(const MyVector<Message>& allMessages)
{
	std::ofstream out(FileNames::MESSAGES, std::ios::trunc);

	for (size_t i = 0; i < allMessages.size(); ++i)
	{
		const Message& msg = allMessages[i];
		out << msg.getSenderID() << GeneralConstants::DELIMETER
			<< msg.getRecipientID() << GeneralConstants::DELIMETER
			<< msg.getTimeStamp() << GeneralConstants::DELIMETER
			<< msg.getIsDeleted() << GeneralConstants::DELIMETER
			<< msg.getContent() << '\n';
	}

	out.close();
}
void DataHandler::saveAssignments(const MyVector<Course>& courses)
{
	std::ofstream out(FileNames::ASSIGNMENTS, std::ios::trunc);

	for (size_t i = 0; i < courses.size(); ++i)
	{
		const Course& course = courses[i];
		for (size_t j = 0; j < course.getAssignments().size(); j++)
		{
			const Assignment& a = course.getAssignments()[j];
			out << a.getId() << GeneralConstants::DELIMETER
				<< a.getCourseID() << GeneralConstants::DELIMETER
				<< a.getTitle() << '\n';
		}
	}
	out.close();
}
void DataHandler::saveSubmissions(const MyVector<Course>& courses)
{
	std::ofstream out(FileNames::SUBMISSIONS, std::ios::trunc);
	if (!out.is_open())
	{
		throw std::runtime_error(ErrorMessages::FILE_NOT_FOUND);
	}

	for (size_t i = 0; i < courses.size(); ++i)
	{
		const MyVector<Assignment>& assignments = courses[i].getAssignments();
		for (size_t j = 0; j < assignments.size(); ++j)
		{
			const Assignment& assignment = assignments[j];
			const MyVector<Submission>& submissions = assignment.getSubmissions();

			for (size_t k = 0; k < submissions.size(); ++k)
			{
				const Submission& sub = submissions[k];

				out << sub.getAssignmentId() << GeneralConstants::DELIMETER
					<< sub.getStudentId() << GeneralConstants::DELIMETER
					<< sub.getGrade() << GeneralConstants::DELIMETER
					<< sub.getSolution().c_str() << GeneralConstants::DELIMETER
					<< sub.getComment() << '\n';
			}
		}
	}

	out.close();
}