#include "Manager.h"
#include <sstream>

Manager::Manager(const std::string &new_domain) :
	domain(new_domain)
{
	if (!bootUp()) throw "Could not boot";
}


Manager::~Manager()
{
	shutDown();
}

bool Manager::bootUp()
{
	std::ostringstream mail_file, user_file;
	mail_file << domain << "_mails.txt";
	user_file << domain << "_users.txt";
	if(mailList.load(mail_file.str()) && userList.load(user_file.str())) return true;
	else return false;
}

void Manager::shutDown()
{
	std::ostringstream mail_file, user_file;
	mail_file << domain << "_mails.txt";
	user_file << domain << "_users.txt";
	mailList.save(mail_file.str());
	userList.save(user_file.str());
}

User* Manager::registerUser()
{
	User* n = nullptr;
	return n; //Placeholder
}

User* Manager::createAccount()
{
	User* n = nullptr;
	return n; //Placeholder
}

void Manager::sendMail(User &user, const std::string idMail)
{

}

void Manager::terminateMail(User &user, const std::string &idMail)
{

}