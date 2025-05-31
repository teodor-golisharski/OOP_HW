#pragma once
#include "User.h"
#include "MyString.hpp"
#include "MyVector.hpp"
#include "Assignment.h"

class Teacher : public User
{
private:


public:
    Teacher(int id, const MyString& firstName, const MyString& lastName, const MyString& password);

    virtual User* clone() const override;
    virtual const MyString& getRoleString() const override;
};

