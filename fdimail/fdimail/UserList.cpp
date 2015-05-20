#include "UserList.h"

bool UserList::insert(User* elem)
{
	//resize if necessary
	if (!full())
	{
		//Look for corresponding position
		int pos;
		search(elem->getId(), pos);
		//Make space for newcomer
		shiftRight(pos);
		//Insert the elem
		list[pos] = elem;
		counter++;
		return true;
	}
	else return false;
}