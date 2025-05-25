#pragma once
#include "Teacher.h"
#include "Student.h"
#include "Assignment.h"

class Course
{
private:
    int id;
    MyString name;
    Teacher* teacher;
    MyString enrollmentPassword;
    MyVector<Student*> students;
    MyVector<Assignment> assignments;

public:
    Assignment* findAssignment(const MyString& assignmentName);
};

