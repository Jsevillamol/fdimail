#ifndef MANAGER
#define MANAGER

#include <string>
#include "MailList.h"
#include "UserList.h"
#include "GraphInter.h"
#include "User.h"

/*
This class is responsible for dealing with every sessions,
so that the mails are sent, or the account are manipulated
It also loads and saves the mails and the users from the save files
*/

class Manager
{
private:
	std::string domain;
	MailList mailList;
	UserList userList;
	ContactList contactList;

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

	void AddFastName(User* user);
	void AliasOptions(Session* session);

	MailList* getMailList(){ return &mailList; }

	void sendMail(User* user, Mail* mail);
	bool answer(User* user, Mail* mail);
	void deleteMail(TrayList* box, const std::string &idMail);
	void deleteName(User* user, const std::string &idName);
};
#endif
