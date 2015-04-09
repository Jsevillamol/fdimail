#ifndef MANAGER
#define MANAGER

#include <string>
#include "MailList.h"
#include "UserList.h"

class Manager
{
private:
	std::string domain;
	MailList mailList;
	UserList userList;
public:
	Manager(const std::string &new_domain);
	~Manager();

	bool bootUp();
	void shutDown();

	User* registerUser();
	User* createAccount();

	void sendMail(User &user, const std::string idMail);
	void terminateMail(User &user, const std::string &idMail);
};
#endif
