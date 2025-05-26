#pragma once
#include "Teacher.h"
#include "Student.h"
#include "Assignment.h"

class Course
{
private:
    int id;
    MyString name;
    MyString enrollmentPassword;

    Teacher* teacher;

    MyVector<Student*> students;
    MyVector<Assignment> assignments;

public:
    Course();
    Course(int id, const MyString& name, Teacher* teacher, const MyString& enrollmentPassword);

    int getId() const;
    const MyString& getName() const;
    Teacher* getTeacher() const;

    Assignment* findAssignment(const MyString& assignmentName);
};

