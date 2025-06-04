// Teodor Golisharski 6MI0600367
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

const char* Admin::getRoleString() const
{
    return "Admin";
}
