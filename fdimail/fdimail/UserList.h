#ifndef USERLIST
#define USERLIST

#include <string>
#include "List.h"
#include "User.h"

class UserList: public List<User, MAX_USERS> {
public:
	bool delete_user(std::string &id){
		int pos;
		if (search(id, pos)){
			delete list[pos];
			shiftLeft(pos);
			return true;
		}
		else return false;
	}

};

#endif