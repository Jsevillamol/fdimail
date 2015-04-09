#ifndef MAILLIST
#define MAILLIST

#include <string>
#include "Mail.h"
#include "GlobalConstants.h"

class MailList
{
private:
	int counter;
	Mail** list;
public:
	MailList(); //init
	~MailList();

	inline bool full()const { return this->counter == MAX_MAILS; }
	inline int lenght()const { return this->counter; }

	bool insert(const Mail &mail);
	bool search(const std::string &idMail, int &pos)const;

	void save(const std::string &name)const;
	bool load(const std::string &name);

	bool terminate(const std::string &idMail);
};
#endif