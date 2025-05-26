#include "Assignment.h"
#include "OutputMessages.h"

Assignment::Assignment(int courseID, const MyString& title)
{
    if (title.length() == 0)
    {
        throw std::invalid_argument(ErrorMessages::EMPTY_ASSIGNMENT_TITLE);
    }
    this->title;
    this->courseID = courseID;
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
