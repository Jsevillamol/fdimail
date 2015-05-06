#include "User.h"

User::User(const std::string idUser, const std::string password):
id(idUser), password(sha1(password)), fastname_count(0)
{}

User::User(){}

//Saves the user datos on the file you choose
void User::save(std::ofstream &file)const
{
	file << this->id << std::endl
		<< this->password << std::endl
		<< this->fastname_count << std::endl;

	for (int i = 0; i < this->fastname_count; i++)
	{
		file << this->fast_names[i].user << " " << this->fast_names[i].alias << std::endl;
	}
	
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
			file >> this->fastname_count;

			if (!file.fail())
			{
				for (int i = 0; i < this->fastname_count && !file.fail(); i++)
				{
					file >> this->fast_names[i].user;
					file >> this->fast_names[i].alias;
				}
				this->outbox.load(file);
				this->inbox.load(file);

				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}