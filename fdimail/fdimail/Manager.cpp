#include "Manager.h"


Manager::Manager(const std::string &new_domain) :
	domain(new_domain)
{
	bootUp();
}


Manager::~Manager()
{

}

bool Manager::bootUp()
{
	return true; //Placeholder
}

void Manager::shutDown()
{

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