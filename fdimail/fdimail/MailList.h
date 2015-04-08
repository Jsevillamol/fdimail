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
	MailList() { init(); }
	~MailList();

	inline void init(){ this->counter = 0; }
	inline bool full()const { return this->counter == MAX_MAILS; }
	inline int lenght()const { return this->counter; }
	void save(const std::string &name)const;
	bool load(const std::string &name);
	bool insert(const Mail &mail);
	bool search(const std::string &idMail, int &pos)const;
	bool terminate(const std::string &idMail);
};
#endif