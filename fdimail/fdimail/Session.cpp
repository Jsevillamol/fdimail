#include "Session.h"
#include "GraphInter.h"

Session::Session(Manager* manager) :
manager(manager)
{
	GraphInter::load();

	int option;
	do{
		option = GraphInter::get()->mainMenu();
		if (option == 1)
			user = manager->createAccount();

		else if (option == 2)
			user = manager->registerUser();

		if (option != 0) launch();
	} while (option != 0);
}

Session::Session() {}

Session::~Session()
{

}

void Session::launch() //to do
{
	Session* sesion = new Session;
	int opt = 1;

	do{
		opt = GraphInter::get()->sessionMenu(this);
		switch (opt)
		{
		case 1:
			readMail();
			break;
		case 2:
			sendMail();
			break;
		case 3:
			deleteMail();
			break;
		case 4:
			user->changeTray();
			break;
		case 5:
			fastRead();
			break;
		}
	} while (opt != 0);
}

void Session::readMail()
{
	//Select mail to read
	std::string id = GraphInter::get()->selectMail(this);
	//Display mail
	Mail* mail = manager->getMailList().get(id);
	GraphInter::get()->drawMail(mail);
	//Change mail status to read
	user->active_tray()->get(id)->read = true;

	GraphInter::get()->pause();

	if (GraphInter::get()->mailMenu())
	{
		GraphInter::get()->answerMail(*mail);
	}
}

void Session::fastRead()
{
	//for mail not read
	
	for (int i = 0; i < user->active_tray()->lenght(); i++)
	{
		if (!(*(user->active_tray()))[i]->read)
		{
			std::string id = (*(user->active_tray()))[i]->getId();
			//Display mail
			GraphInter::get()->drawMail(manager->getMailList().get(id));
			//Change mail status to read
			user->active_tray()->get(id)->read = true;

			GraphInter::get()->pause();
		}
	}
}

void Session::sendMail()
{
	manager->sendMail(user, GraphInter::get()->newMail(user->getId()));
}

void Session::deleteMail()
{
	//Select mail
	std::string id = GraphInter::get()->selectMail(this);
	//Delete
	manager->deleteMail(user, id);
}
