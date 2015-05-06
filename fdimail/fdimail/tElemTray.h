#ifndef TELEMENTRAY
#define TELEMENTRAY

#include <string>

/*
This struct is responsible for load and save the id of a mail
and its read status
*/

struct tElemTray
{
	std::string idMail;
	bool read;

	tElemTray() {}
	tElemTray(std::string idMail) : idMail(idMail), read(false) {}
	std::string getId() const { return idMail; }

	void save(std::ofstream &file)
	{
		file << this->idMail << " " << this->read << std::endl;
	}
	void load(std::ifstream &file)
	{
		file >> this->idMail >> this->read;
	}
};

#endif