#ifndef MANAGER
#define MANAGER

#include <string>
#include "MailList.h"
#include "UserList.h"

/*
This class is responsible for dealing with every sessions,
so that the mails are sent, or the account are manipulated
It also loads and saves the mails and the users from the save files
It acts as the backend server
*/

class Manager
{
public:
	Manager(const std::string &new_domain);
	~Manager();

	void bootUp();
	void shutDown();

	static Manager* getManager(){ return manager; }

	MailList* getMailList(){ return &mailList; }
	UserList* getUserList(){ return &userList; }

	std::string getDomain(){ return domain; }

	User* registerUser();
	User* createAccount();

	void deleteAccount(const std::string &id);

	void sendMail(User* user, Mail* mail);
	bool answer(User* user, Mail* mail);
	void deleteMail(TrayList* box, const std::string &idMail);

private:
	static Manager* manager;

	std::string domain;
	MailList mailList;
	UserList userList;

	void manualUsers(std::string &name);
	void manualMails(std::string &name);
};
#endif
