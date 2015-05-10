#ifndef USERLIST
#define USERLIST

#include <string>
#include "List.h"
#include "User.h"
#include "GlobalConstants.h"

/*
Derived class from list, responsible
for work whith users
*/

class UserList: public List<User, MAX_USERS> {};

#endif