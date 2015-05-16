#ifndef TCONTACT
#define TCONTACT

#include <string>
#include <fstream>

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
};

#endif