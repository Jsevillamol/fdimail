#include "Session.h"
#include "GraphInter.h"

Session::Session(Manager* manager):
manager(manager)
{
	int option = GraphInter::get()->mainMenu();
	if (option == 1)
		user = manager->createAccount();
	else if (option == 2)
		user = manager->registerUser();
}

Session::~Session()
{

}

void Session::readMail()
{
	//Select mail to read
	int pos = 0; //= int(GraphInter::get()->inputBox(std::string("Which mail?")));
	//Search mail
	std::string id = (*(user->active_tray()))[pos]->getId();
	//Display mail
	GraphInter::get()->drawMail(manager->mailList.get(id));
	//Change mail status to read
	(*(user->active_tray()))[pos]->read = true;

	GraphInter::get()->pause();

	if (GraphInter::get()->mailMenu()); //Answer mail
}

void Session::sendMail()
{
	Mail* mail = new Mail;
	manager->sendMail(user, mail->newMail(user->getId()));
}

void Session::deleteMail()
{

}

void Session::fastRead()
{

}
