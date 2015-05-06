#include "User.h"

User::User(const std::string idUser, const std::string password):
id(idUser), password(sha1(password))
{}

User::User(){}

void User::save(std::ofstream &file)const
{
	file << this->id << std::endl 
		<< this->password << std::endl;
	
	this->outbox.save(file);
	this->inbox.save(file);
}

bool User::load(std::ifstream &file)
{
	file >> this->id;

	if (!file.fail())
	{
		file >> this->password;

		if (!file.fail())
		{
			this->outbox.load(file);
			this->inbox.load(file);

			return true;
		}
		else return false;
	}
	else return false;
}