#ifndef TCONTACT
#define TCONTACT

#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

/*----------------------------
This struct is responsible for load and save 
the id of an user and its associated alias;
it also turns an user and its alias to string
------------------------------*/

struct tContact
{
	std::string user;
	std::string alias;

	tContact(std::string realName, std::string fastName) : user(realName), alias(fastName) {}
	tContact() {}
	
	std::string& getId() { return alias; }
	std::string& getAddress() { return user; }

	void save(std::ofstream &file)const
	{
		file << (this->user) << " " << (this->alias) << std::endl;
	}

	void load(std::ifstream &file)
	{
		file >> (this->user) >> (this->alias);
	}

	std::string header()
	{
		std::ostringstream contact;

		contact << std::setw(36) << std::left << this->user << std::left << this->alias;

		return contact.str();
	}
};
#endif