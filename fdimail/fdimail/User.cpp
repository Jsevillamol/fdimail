#include "User.h"

User::User(const std::string idUser, const std::string password):
id(idUser), password(sha1(password)), contactList(idUser)
{}

User::User(): contactList(){}

//Saves the user datos on the file you choose
void User::save(std::ofstream &file)const
{
	file << this->id << std::endl
		<< this->password << std::endl;

	this->contactList.save(file);
	this->outbox.save(file);
	this->inbox.save(file);
}

//Loads the user datos from the file you choose
bool User::load(std::ifstream &file)
{
	file >> this->id;

	if (!file.fail())
	{
		file >> this->password;

		if (!file.fail())
		{
			this->contactList.load(file);
			this->outbox.load(file);
			this->inbox.load(file);

			return true;
		}
		else return false;
	}
	else return false;
}