#ifndef USERLIST
#define USERLIST

#include "GlobalConstants.h"
#include <string>
#include "List.h"
#include "User.h"

/*----------------------------
Derived class from list, responsible
for holding the user database
------------------------------*/

class UserList: public List<User> 
{
private:
	bool full() { return this->counter == MAX_USERS; }

public:

	bool UserList::insert(User* elem)
	{
		if (!full())
		{
			//Look for corresponding position
			int pos;
			int left_key = 0, right_key = counter - 1;
			search(elem->getId(), pos, left_key, right_key);
			//Make space for newcomer
			shiftRight(pos);
			//Insert the elem
			list[pos] = elem;
			counter++;
			return true;
		}
		else return false;
	}
};
#endif