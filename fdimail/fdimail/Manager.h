#ifndef MANAGER
#define MANAGER

#include <string>
#include "MailList.h"
#include "UserList.h"
#include "GraphInter.h"
#include "User.h"

class Manager
{
private:
	std::string domain;
	MailList mailList;
	GraphInter inter;
	UserList userList;

	friend class Session;
public:
	Manager(const std::string &new_domain);
	~Manager();

	bool bootUp();
	void shutDown();

	User* registerUser();
	User* createAccount();

	MailList getMailList(){ return mailList; }

	void sendMail(User* user, Mail* mail);
	void deleteMail(User* user, const std::string &idMail);
};
#endif
