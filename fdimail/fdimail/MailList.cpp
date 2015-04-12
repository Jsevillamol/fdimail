#include "MailList.h"

bool MailList::load(const std::string &name)
{
	return true; //Placeholder
}

bool MailList::delete_mail(const std::string &id)
{
	int pos;
	if (search(id, pos))
	{
		list[pos]->lowerCounter();
		if (list[pos]->getCounter() == 0)
			destroy(id);
		return true;
	}
	else return false;
}