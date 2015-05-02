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
	UserList userList;

	void manualyUsers(std::string &name);
	void manualyMails(std::string &name);

public:
	Manager(const std::string &new_domain);
	~Manager();

	void bootUp();
	void shutDown();

	User* registerUser();
	User* createAccount();

	MailList* getMailList(){ return &mailList; }

	bool sendMail(User* user, Mail* mail);
	void deleteMail(TrayList* box, const std::string &idMail);
};
#endif
