#include "IdGenerator.h"

int IdGenerator::nextUser()
{
    return nextUserId++;
}

int IdGenerator::nextCourse()
{
    return nextCourseId++;
}

int IdGenerator::nextAssignment()
{
    return nextAssignmentId++;
}

void IdGenerator::loadFromFile()
{
    std::ifstream in(FileNames::ID_GENERATOR);
    if (!in.is_open())
    {
        throw std::runtime_error(ErrorMessages::FILE_NOT_FOUND);
    }

    in >> nextUserId;
    in >> nextCourseId;
    in >> nextAssignmentId;

    in.close();
}

void IdGenerator::saveToFile() const
{
    std::ofstream out(FileNames::ID_GENERATOR);
    if (!out.is_open())
    {
        throw std::runtime_error(ErrorMessages::FILE_NOT_FOUND);
    }

    out << nextUserId << '\n'
        << nextCourseId << '\n'
        << nextAssignmentId << '\n';

    out.close();
}
