#ifndef TELEMENTRAY
#define TELEMENTRAY

#include <string>

struct tElemTray
{
	std::string idMail;
	bool read;

	tElemTray(std::string idMail) : idMail(idMail), read(false) {}
	
};

#endif