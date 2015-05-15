#ifndef MAILLIST
#define MAILLIST

#include <string>
#include "List.h"
#include "Mail.h"
#include "GlobalConstants.h"

/*
Derived class from list, responsible 
for work whith all mails
*/

class MailList: public List<Mail, MAX_MAILS>
{
public:
	//Deletes the mail you want from the maillist
	bool MailList::delete_mail(const std::string &id)
	{
		int pos;
		if (search(id, pos))
		{
			list[pos]->lowerCounter();
			if (list[pos]->getCounter() <= 0)
				destroy(id);
			return true;
		}
		else return false;
	}

	Mail* getError(){ return &error; }

private:
	Mail error;
};
#endif