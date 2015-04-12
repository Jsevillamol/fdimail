#ifndef MAILLIST
#define MAILLIST

#include <string>
#include "List.h"
#include "Mail.h"
#include "GlobalConstants.h"

class MailList: public List<Mail, MAX_MAILS>
{
public:
	bool load(const std::string &name);

	bool delete_mail(const std::string &id);
};
#endif