#include "Admin.h"

Admin::Admin(int id, const MyString& firstName, const MyString& lastName, const MyString& password)
    :User(id, firstName, lastName, password)
{
    this->role = UserRole::Admin;
}

User* Admin::clone() const
{
    return new Admin(*this);
}

const MyString& Admin::getRoleString() const
{
    return "Admin";
}
