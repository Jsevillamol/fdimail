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
	
	std::string getId() { return user; }
	std::string getAlias() { return alias; }

	void save(std::ofstream &file)const
	{
		file << (this->user) << std::endl
			<< (this->alias) << std::endl;
	}

	bool load(std::ifstream &file)
	{
		if (!file.fail())
		{
			file >> (this->user) >> (this->alias);
			return true;
		}
		else return false;
	}
};

#endif