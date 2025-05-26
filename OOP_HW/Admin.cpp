#include "Admin.h"

Admin::Admin()
{
    std::cout << "";
}

const UserRole Admin::getRole() const
{
    return UserRole::Admin;
}

User* Admin::clone() const
{
    return new Admin(*this);
}
