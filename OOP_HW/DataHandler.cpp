#pragma once
#include <iostream>
#include <fstream>

#include "DataHandler.h"
#include "ApplicationConstants.h"

void DataHandler::loadCourses(MyVector<Course>& courses)
{

}
void DataHandler::loadUsers(MyVector<User*>& users)
{

}
void DataHandler::loadMessages(MyVector<Message>& messages)
{
    std::ifstream in(FileNames::MESSAGES);

    if (!in.is_open()) return;

    char buffer[1024];
    while (in.getline(buffer, 1024))
    {
        MyString line(buffer);
        MyVector<MyString> tokens = line.split('|');

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
void DataHandler::loadAssignments(MyVector<Assignment>& assignments)
{

}
void DataHandler::loadSubmissions(MyVector<Submission>& submissions, const MyVector<User*>& users)
{
    std::ifstream in(FileNames::SUBMISSIONS);
    if (!in.is_open()) return;

    char buffer[1024];

    while (in.getline(buffer, 1024))
    {
        MyString line(buffer);
        MyVector<MyString> tokens = line.split('|');
        if (tokens.size() < 3) continue;

        int studentID = tokens[0].toInt();
        double grade = tokens[1].toDouble(); 
        MyString solution = tokens[2];

        Student* student = nullptr;
        for (size_t i = 0; i < users.size(); i++)
        {
            if (users[i]->getId() == studentID && users[i]->getRole() == UserRole::Student)
            {
                student = dynamic_cast<Student*>(users[i]);
                break;
            }
        }

        throw std::runtime_error("");

        Submission sub(student, solution);
        sub.internalSetGrade(grade); 
        submissions.push(sub);
    }

    in.close();
}



void DataHandler::saveCourses(const MyVector<Course>& courses)
{

}
void DataHandler::saveUsers(const MyVector<User*>& users)
{

}
void DataHandler::saveMessages(const MyVector<Message>& allMessages)
{
    std::ofstream out(FileNames::MESSAGES);

    for (size_t i = 0; i < allMessages.getCapacity(); ++i)
    {
        const Message& msg = allMessages[i];
        out << msg.getSenderID() << '|'
            << msg.getRecipientID() << '|'
            << msg.getTimeStamp() << '|'
            << msg.getIsDeleted() << '|'
            << msg.getContent() << '\n';
    }

    out.close();
}
void DataHandler::saveAssignments(const MyVector<Assignment>& assignments)
{

}

void DataHandler::saveSubmissions(const MyVector<Submission>& submissions)
{
    std::ofstream out(FileNames::SUBMISSIONS);
    if (!out.is_open()) return;

    for (size_t i = 0; i < submissions.size(); i++)
    {
        const Submission& s = submissions[i];
        out << s.getStudentId() << '|'
            << s.getGrade() << '|'
            << s.getSolution().c_str() << '\n';
    }

    out.close();
}