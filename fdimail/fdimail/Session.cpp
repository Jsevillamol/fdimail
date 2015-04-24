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

		if (user != nullptr && option != 0)
		{
			GraphInter::get()->clearConsole();
			launch();
		}
		GraphInter::get()->clearConsole();
	} while (option != 0);
}

void Session::launch()
{
	int opt;

	do{
		opt = GraphInter::get()->sessionMenu(this);
		GraphInter::get()->clearConsole();
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
			GraphInter::get()->clearConsole();
			break;
		case 5:
			GraphInter::get()->clearConsole();
			fastRead();
			break;
		}
		GraphInter::get()->clearConsole();
	} while (opt != 0);
}

void Session::readMail()
{
	if (this->getUser()->active_tray()->lenght() == 0)
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
		user->active_tray()->get(id)->read = true;

		GraphInter::get()->pause();

		if (GraphInter::get()->mailMenu())
		{
			GraphInter::get()->answerMail(*mail);
		}
	}
}

void Session::fastRead()
{
	int j, i;
	
	for (j = 0; j < user->active_tray()->lenght() && (*(user->active_tray()))[j]->read; j++) {}

	if (j == user->active_tray()->lenght() - 1 && (*(user->active_tray()))[j]->read)
	{
		GraphInter::get()->error("You do not have any unread mails");
		GraphInter::get()->pause();
		GraphInter::get()->clearConsole();
	}
	else
	{
		for (i = 0; i < user->active_tray()->lenght(); i++)
		{
			if (!(*(user->active_tray()))[i]->read)
			{
				std::string id = (*(user->active_tray()))[i]->getId();
				//Display mail
				GraphInter::get()->drawMail(manager->getMailList()->get(id));
				//Change mail status to read
				user->active_tray()->get(id)->read = true;

				GraphInter::get()->error("\n");
				GraphInter::get()->linea();
				GraphInter::get()->pause();
			}
		}
		GraphInter::get()->clearConsole();
	}
}

void Session::sendMail()
{
	GraphInter::get()->clearConsole();
	manager->sendMail(user, GraphInter::get()->newMail(user->getId()));
}

void Session::deleteMail()
{
	if (this->getUser()->active_tray()->lenght() == 0)
	{
		GraphInter::get()->error("Error, you have no mails to delete");
		GraphInter::get()->pause();
		GraphInter::get()->clearConsole();
	}
	else
	{
		int option = GraphInter::get()->WhatToDelete();
		int longitud = this->getUser()->active_tray()->lenght();

		if (option == 1)
		{
			//Select mail
			std::string id = GraphInter::get()->selectMail(this);

			GraphInter::get()->clearConsole();
			//Delete
			manager->deleteMail(user, id);
		}
		else if (option == 0)
		{

			GraphInter::get()->clearConsole();

			for (int i = 0; i < longitud; i++)
			{
				std::string newId = (*(this->getUser()->active_tray()))[0]->idMail;

				manager->deleteMail(user, newId);
			}
		}
	}
}
