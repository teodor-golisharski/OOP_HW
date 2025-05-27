#include "Assignment.h"
#include "OutputMessages.h"

Assignment::Assignment() : title(""), id(-1), courseId(-1) {}

Assignment::Assignment(int id, int courseID, const MyString& title)
{
    if (title.length() == 0)
    {
        throw std::invalid_argument(ErrorMessages::EMPTY_ASSIGNMENT_TITLE);
    }
    this->title;
    this->id = id;
    this->courseId = courseID;
}

int Assignment::getId() const
{
    return this->id;
}

int Assignment::getCourseID() const
{
    return this->courseId;
}

const MyString& Assignment::getTtile() const
{
    return this->title;
}

const MyVector<Submission>& Assignment::getSubmissions() const
{
    return this->submissions;
}

Submission& Assignment::findSubmission(int studentId)
{
    for (size_t i = 0; i < submissions.getCapacity(); i++)
    {
        if (submissions[i].getStudentId() == studentId)
        {
            return submissions[i];
        }
    }
    throw std::invalid_argument(ErrorMessages::GENERAL_ERROR);
}

void Assignment::addSubmission(const Submission& sub)
{
    this->submissions.push(sub);
}
