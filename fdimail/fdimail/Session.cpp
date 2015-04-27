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
		{
			GraphInter::get()->clearConsole();
			user = manager->createAccount();
		}
		else if (option == 2)
		{
			GraphInter::get()->clearConsole();
			user = manager->registerUser();
		}
		if (user != nullptr && option != 0)
		{
			GraphInter::get()->clearConsole();
			launch();
		}
		GraphInter::get()->clearConsole();
	} while (option != 0);
}

Session::~Session()
{
	GraphInter::close();
}

void Session::launch()
{
	active_list = false;
	int opt;

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
			changeTray();
			GraphInter::get()->clearConsole();
			break;
		case 5:
			GraphInter::get()->clearConsole();
			fastRead();
			break;
		}
	} while (opt != 0);
}

void Session::readMail()
{
	if (this->active_tray()->lenght() == 0)
	{
		GraphInter::get()->error("Error, you have no mails to read");
		GraphInter::get()->pause();
		GraphInter::get()->clearConsole();
	}
	else
	{
		//Select mail to read
		std::string id = GraphInter::get()->selectMail(this);
		GraphInter::get()->clearConsole();
		//Display mail
		Mail* mail = manager->getMailList()->get(id);
		GraphInter::get()->drawMail(mail);
		//Change mail status to read
		active_tray()->get(id)->read = true;

		GraphInter::get()->pause();
		int option = GraphInter::get()->mailMenu();

		GraphInter::get()->clearConsole();

		if (option == 1)
		{
			GraphInter::get()->answerMail(*mail);
		}
		else if (option == 2)
		{
			GraphInter::get()->forward(*mail);
		}
	}
}

void Session::fastRead()
{	
	if (active_tray()->lenght() == 0)
	{
		GraphInter::get()->error("You do not have any mail on your active tray");
		GraphInter::get()->pause();
		GraphInter::get()->clearConsole();
	}
	else
	{
		bool something_to_read = false;
		for (int i = 0; i < active_tray()->lenght(); i++)
		{
			if (!active_tray()->operator[](i)->read)
			{
				something_to_read = true;
				std::string id = active_tray()->operator[](i)->getId();
				//Display mail
				GraphInter::get()->drawMail(manager->getMailList()->get(id));
				//Change mail status to read
				active_tray()->operator[](i)->read = true;

				GraphInter::get()->error("\n");
				GraphInter::get()->linea();
				GraphInter::get()->pause();
			}
		}
		if (!something_to_read)
		{
			GraphInter::get()->error("You do not have any unread mail");
			GraphInter::get()->pause();
		}
		GraphInter::get()->clearConsole();
	}
}

void Session::sendMail()
{
	GraphInter::get()->clearConsole();

	Mail* mail = GraphInter::get()->newMail(user->getId());

	if (mail == nullptr)
	{
		GraphInter::get()->error("Mail not sent");
		GraphInter::get()->pause();
	}
	else
	{
		if (!manager->sendMail(user, mail))
		{
			GraphInter::get()->error("The mail could not be sent, destinatary not found");
			GraphInter::get()->pause();
		}
	}
	GraphInter::get()->clearConsole();
}

void Session::deleteMail()
{
	if (this->active_tray()->lenght() == 0)
	{
		GraphInter::get()->error("Error, you have no mails to delete");
		GraphInter::get()->pause();
		GraphInter::get()->clearConsole();
	}
	else
	{
		int option = GraphInter::get()->WhatToDelete();
		int longitud = this->active_tray()->lenght();

		if (option == 1)
		{
			//Select mail
			std::string id = GraphInter::get()->selectMail(this);			
			//Delete
			manager->deleteMail(active_tray(), id);
			GraphInter::get()->clearConsole();
		}
		else if (option == 0)
		{

			GraphInter::get()->clearConsole();

			for (int i = 0; i < longitud; i++)
			{
				std::string newId = (*(this->active_tray()))[0]->idMail;

				manager->deleteMail(active_tray(), newId);
			}
		}
	}
}
