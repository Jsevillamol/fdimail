#ifndef TCONTACT
#define TCONTACT

#include <string>

struct tContact
{
	std::string user;
	std::string alias;

	tContact(std::string realName, std::string fastName) : user(realName), alias(fastName) {}
	tContact() {}

	void save(std::ofstream &file)const;
	bool load(std::ifstream &file);
};

#endif