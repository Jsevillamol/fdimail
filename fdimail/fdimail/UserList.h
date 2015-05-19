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

class UserList: public List<User> {};

#endif