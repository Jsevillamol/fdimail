#include "ContactList.h"

std::string ContactList::SearchFastName(std::string &name)
{
	bool is_alias = true;
	bool alias_found = false;
	int i;

	for (int j = 0; j < name.size() && is_alias; j++)
	{
		if (name[j] == '@')
		{
			return name; //If it has a @ it is a direction
		}
	}

	for (i = 0; i < user->getNameCount() && !alias_found; i++)
	{
		if (user->getNumName(i).alias == name)
		{
			alias_found = true;
		}
	}

	if (alias_found) return user->getNumName(i).user;
	else return name;

}