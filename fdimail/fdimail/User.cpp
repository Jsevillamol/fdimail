#include "User.h"

User::User(const std::string &idUser, const std::string &password)
{
	active_list = 0;
}

void User::save(std::ofstream &file)const
{
	file << this->id << std::endl 
		<< this->password << std::endl;
	
	this->outbox.save(file);
	this->inbox.save(file);
}

bool User::load(std::ifstream &file)
{
	return true; //Placeholder
}