#ifndef USERLIST
#define USERLIST

#include <string>
#include "List.h"
#include "User.h"
#include "GlobalConstants.h"

/*
Derived class from list, responsible
for holding the user database
*/

class UserList: public List<User> 
{
private:
	bool full() { return this->counter == MAX_USERS; }

public:
	bool insert(User* user);
};

#endif