#include "User.h"

User::User(const std::string idUser, const std::string password):
id(idUser), password(password)
{
	active_list = 0;
}

User::User(){}

void User::save(std::ofstream &file)const
{
	file << this->id << std::endl 
		<< this->password << std::endl;
	
	this->outbox.save(file);
	this->inbox.save(file);

	file << "X" << std::endl;
}

bool User::load(std::ifstream &file)
{
	bool correct = true;
	std::string ignore;

	file >> this->id;

	if (!file.fail())
	{
		file >> this->password;

		if (!file.fail())
		{
			this->outbox.load(file);
			this->inbox.load(file);

			file >> ignore;
		}
		else correct = false;
	}
	else correct = false;

	return correct;
}