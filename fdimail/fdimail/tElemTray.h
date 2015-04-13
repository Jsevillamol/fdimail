#ifndef TELEMENTRAY
#define TELEMENTRAY

#include <string>

struct tElemTray
{
	std::string idMail;
	bool read;

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