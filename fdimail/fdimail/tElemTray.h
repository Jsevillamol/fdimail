#ifndef TELEMENTRAY
#define TELEMENTRAY

#include <string>
#include "Mail.h"

/*
This struct is responsible for load and save the id of a mail
and its read status
*/

struct tElemTray
{
	Mail* mail;
	bool read;

	tElemTray() {}
	tElemTray(Mail* mail) : mail(mail), read(false) {}

	std::string getId() const { return mail->getId(); }

	void save(std::ofstream &file) const;
	void load(std::ifstream &file);
};

#endif