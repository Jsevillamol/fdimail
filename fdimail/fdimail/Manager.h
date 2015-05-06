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

	void manualUsers(std::string &name);
	void manualMails(std::string &name);

public:
	Manager(const std::string &new_domain);
	~Manager();

	void bootUp();
	void shutDown();

	User* registerUser();
	User* createAccount();

	void deleteAccount(const std::string &id);
	void ChangeUsername(User* user);
	void ChangePassword(User* user);

	MailList* getMailList(){ return &mailList; }

	void sendMail(User* user, Mail* mail);
	bool answer(User* user, Mail* mail);
	void deleteMail(TrayList* box, const std::string &idMail);
};
#endif
