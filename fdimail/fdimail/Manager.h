#ifndef MANAGER
#define MANAGER

#include <string>
#include "MailList.h"
#include "UserList.h"

/*
Manager holds the mail and user databases
He is responsible for loading and saving them to text files
It acts as the backend server, providing service to Sessions requesting GETS and POSTS
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

	void deleteAccount(User* user);

	void sendMail(User* user, Mail* mail);
	bool answer(User* user, Mail* mail);
	void deleteMail(TrayList* box, const std::string &idMail);

private:
	static Manager* manager;

	std::string domain;
	MailList mailList;
	UserList userList;

	void loadUsers(std::string &name);
	void loadMails(std::string &name);
};
#endif
