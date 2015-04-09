#ifndef MAILLIST
#define MAILLIST

#include <string>
#include "List.h"
#include "Mail.h"
#include "GlobalConstants.h"

class MailList: public List<Mail, MAX_MAILS>
{
public:
	void save(const std::string &name)const;
	bool load(const std::string &name);
};
#endif