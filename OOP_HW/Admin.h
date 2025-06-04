// Teodor Golisharski 6MI0600367
#pragma once
#include "User.h"

class Admin : public User
{

public:
	Admin(int id, const MyString& firstName, const MyString& lastName, const MyString& password);
	virtual User* clone() const override;	
	virtual const char* getRoleString() const override;

};

