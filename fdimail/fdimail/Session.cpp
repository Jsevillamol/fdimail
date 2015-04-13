#include "Session.h"
#include "GraphInter.h"

Session::Session(Manager* manager) :
manager(manager)
{
	int option = GraphInter::get()->logMenu();
	if (option == 1)
		user = manager->createAccount();

	else if (option == 2)
		user = manager->registerUser();

	if (user != nullptr) launch();
}

Session::Session() {}

Session::~Session()
{

}

void Session::launch() //to do
{
	int opt = 1;
	Session* sesion = new Session;
	do{
		GraphInter::get()->drawTraylist(user->active_tray());
		opt = GraphInter::get()->mainMenu(sesion);
		switch (opt){
		case 1:
			readMail();
			break;
		case 2:
			deleteMail();
			break;
		case 3:
			break;
		}
	} while (opt != 0);
}

void Session::readMail()
{
	//Select mail to read
	std::string id = GraphInter::get()->selectMail(user->active_tray());
	//Display mail
	Mail* mail = manager->mailList.get(id);
	GraphInter::get()->drawMail(mail);
	//Change mail status to read
	user->active_tray()->get(id)->read = true;

	GraphInter::get()->pause();

	if (GraphInter::get()->mailMenu())
	{
		Mail* new_mail = new Mail();
		new_mail->answerMail(mail);
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
			GraphInter::get()->drawMail(manager->mailList.get(id));
			//Change mail status to read
			user->active_tray()->get(id)->read = true;

			GraphInter::get()->pause();
		}
	}
}

void Session::sendMail()
{
	Mail* mail = new Mail;
	manager->sendMail(user, mail->newMail(user->getId()));
}

void Session::deleteMail()
{
	//Select mail
	std::string id = GraphInter::get()->selectMail(user->active_tray());
	//Delete
	manager->deleteMail(user, id);
}
