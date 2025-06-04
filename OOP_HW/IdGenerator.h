// Teodor Golisharski 6MI0600367
#pragma once
#include "ApplicationConstants.h"
#include "OutputMessages.h"
#include <fstream>

class IdGenerator
{
    int nextUserId = 100;
    int nextCourseId = 100;
    int nextAssignmentId = 100;

public:
    int nextUser();
    int nextCourse();
    int nextAssignment();

    void loadFromFile();
    void saveToFile() const;
};

