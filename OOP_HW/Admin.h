#pragma once
#include "User.h"

class Admin : public User
{


public:
	Admin();

	virtual const UserRole getRole() const override;
	virtual User* clone() const override;

	
};

