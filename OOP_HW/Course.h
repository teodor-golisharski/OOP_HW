// Teodor Golisharski 6MI0600367
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

    void addAssignment(const Assignment& a);
    void addStudent(Student* user);
    bool hasStudent(int studentId) const;

    friend class DataHandler;
    friend class SystemManager;
public:
    Course() = default;
    Course(int id, const MyString& name, Teacher* teacher, const MyString& enrollmentPassword);

    int getId() const;
    const MyString& getName() const;
    const MyString& getEnrollmentPassword() const;

    Teacher* getTeacher() const;

    Assignment* findAssignmentById(int id);
    Assignment* findAssignmentByName(const MyString& name);
    const MyVector<Assignment>& getAssignments() const;
};