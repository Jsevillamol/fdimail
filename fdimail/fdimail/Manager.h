#ifndef MANAGER
#define MANAGER

#include <string>
#include "User.h"

class Manager
{
private:
	std::string domain;
public:
	Manager();
	~Manager();

	bool bootUp(const std::string &domain);
	void shutDown();
	User* registerUser();
	User* creatAccount();
	void sendMail(User &user, const std::string idMail);
	void terminateMail(User &user, const std::string &idMail);
};
#endif
