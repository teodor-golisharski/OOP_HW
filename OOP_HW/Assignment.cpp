// Teodor Golisharski 6MI0600367
#include "Assignment.h"
#include "OutputMessages.h"
#include "Utilities.h"

Assignment::Assignment() : title(""), id(-1), courseId(-1) {}

Assignment::Assignment(int id, int courseID, const MyString& title)
{
    if (!validateString(title))
    {
        throw std::invalid_argument(ErrorMessages::EMPTY_ASSIGNMENT_TITLE);
    }
    this->title = title;
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

const MyString& Assignment::getTitle() const
{
    return this->title;
}

const MyVector<Submission>& Assignment::getSubmissions() const
{
    return this->submissions;
}


Submission* Assignment::findSubmission(int studentId)
{
    for (size_t i = 0; i < submissions.size(); i++)
    {
        if (submissions[i].getStudentId() == studentId)
        {
            return &submissions[i];
        }
    }
    return nullptr;
}

bool Assignment::hasSubmitted(int studentId) const
{
    for (size_t i = 0; i < submissions.size(); i++)
    {
        if (submissions[i].getStudentId() == studentId)
        {
            return true;
        }
    }

    return false;
}

void Assignment::addSubmission(const Submission& sub)
{
    this->submissions.push(sub);
}

