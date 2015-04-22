#ifndef USERLIST
#define USERLIST

#include <string>
#include "List.h"
#include "User.h"

class UserList: public List<User, MAX_USERS> {};

#endif