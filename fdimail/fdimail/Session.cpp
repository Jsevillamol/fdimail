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

/****************************************************************/
/*                            MENUS                             */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

//Internal part of sessionMenu(), it lets you 
//choose what to do on your session 
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
		case 6:
			GraphInter::get()->clearConsole();
			AccountOptions(opt);
			GraphInter::get()->clearConsole();
		case 7:
			GraphInter::get()->clearConsole();
			manager->AliasOptions(this);
			GraphInter::get()->clearConsole();
		}
	} while (opt != 0);
}

//Internal part of AccountOptions(), it
//let you choose what to do with your
//account
void Session::AccountOptions(int &option)
{
	int menu = GraphInter::get()->AccountOptions();

	if (menu == 1)
	{
		manager->ChangeUsername(user);
	}
	else if (menu == 2)
	{
		manager->ChangePassword(user);
	}
	else if (menu == 3)
	{
		manager->deleteAccount(user->getId());
		option = 0;
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                                 MAIN MENU OPTIONS                                 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

//It shows you the mail you choose, 
//so you can read it
void Session::readMail()
{
	if (this->active_tray()->length() == 0)
	{
		GraphInter::get()->display("Error, you have no mails to read");
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
			answerMail(mail);
		}
		else if (option == 2)
		{
			forwardMail(mail);	
		}
	}
}

//It shows you all the mails that you did not
//read from your imput box
void Session::fastRead()
{	
	if (active_tray()->length() == 0)
	{
		GraphInter::get()->display("You do not have any mail on your active tray");
		GraphInter::get()->pause();
		GraphInter::get()->clearConsole();
	}
	else
	{
		bool something_to_read = false;
		for (int i = active_tray()->length() - 1; i >= 0; i--)
		{
			if (!active_tray()->operator[](i)->read)
			{
				something_to_read = true;
				std::string id = active_tray()->operator[](i)->getId();
				//Display mail
				GraphInter::get()->drawMail(manager->getMailList()->get(id));
				//Change mail status to read
				active_tray()->operator[](i)->read = true;

				GraphInter::get()->linea();
				GraphInter::get()->pause();
			}
		}
		if (!something_to_read)
		{
			GraphInter::get()->display("You do not have any unread mail");
			GraphInter::get()->pause();
		}
		GraphInter::get()->clearConsole();
	}
}

//If it can, sends the mail to the users who must be sent
void Session::sendMail()
{
	GraphInter::get()->clearConsole();

	Mail* mail = GraphInter::get()->newMail(user->getId());

	if (mail == nullptr)
	{
		GraphInter::get()->display("Mail not sent");
		GraphInter::get()->pause();
	}
	else
	{
		manager->sendMail(user, mail);
	}
	GraphInter::get()->clearConsole();
}

//If it can, sends an ansewr mail
void Session::answerMail(Mail* &originalMail)
{
	GraphInter::get()->clearConsole();

	Mail* answer = GraphInter::get()->answerMail(originalMail, user->getId());

	if (answer == nullptr)
	{
		GraphInter::get()->display("Mail not sent");
	}
	else
	{
		manager->answer(user, answer);
	}
	GraphInter::get()->pause();
	GraphInter::get()->clearConsole();
}

//If it can, sends a forward mail
void Session::forwardMail(Mail* &originalMail)
{
	GraphInter::get()->clearConsole();

	Mail* forward = GraphInter::get()->forward(originalMail, user->getId());

	if (forward == nullptr)
	{
		GraphInter::get()->display("Mail not sent");
	}
	else
	{
		manager->sendMail(user, forward);
	}
	GraphInter::get()->pause();
	GraphInter::get()->clearConsole();
}

//Deletes the mail you choose from the tray where you are
void Session::deleteMail()
{
	if (this->active_tray()->length() == 0)
	{
		GraphInter::get()->display("Error, you have no mails to delete");
		GraphInter::get()->pause();
		GraphInter::get()->clearConsole();
	}
	else
	{
		int option = GraphInter::get()->WhatToDelete();
		int longitud = this->active_tray()->length();

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



