#include "tElemTray.h"
#include "Manager.h"

void tElemTray::save(std::ofstream &file)
{
	file << (this->mail->getId()) << " " << (this->read) << std::endl;
}

void tElemTray::load(std::ifstream &file)
{
	std::string idMail;
	(file >> idMail) >> this->read;
	this->mail = Manager::getManager()->getMailList()->get(idMail);
}