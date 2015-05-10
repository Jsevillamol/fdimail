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
		GraphInter::get()->clearConsole();

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
			break;
		case 5:
			fastRead();
			break;
		case 6:
			AccountOptions(opt);
			break;
		case 7:
			AliasOptions();
			break;
		}
	} while (opt != 0);
}

//Internal part of AccountOptions(), it
//let you choose what to do with your
//account
void Session::AccountOptions(int &option)
{
	int menu;
	
	do
	{
		GraphInter::get()->clearConsole();

		menu = GraphInter::get()->AccountOptions();

		if (menu == 1)
		{
			changeUsername();
		}
		else if (menu == 2)
		{
			changePassword();
		}
		else if (menu == 3)
		{
			manager->deleteAccount(user->getId());
			option = 0;
		}
	} while (menu != 0 && option != 0);
}

//Allow you to change your username
//To do: Move this to session
void Session::changeUsername()
{
	bool name_ok;
	std::string data;

	do
	{
		GraphInter::get()->clearConsole();

		name_ok = true;

		data = GraphInter::get()->valid_user();

		if (manager->getUserList()->get(data) != nullptr)
		{
			GraphInter::get()->display("This username already exists");
			GraphInter::get()->pause();

			name_ok = false;
		}
	} while (!name_ok);


	GraphInter::get()->checkUsername(data);

	user->setId(data);
}

//Allow you to change your password
void Session::changePassword()
{
	std::string data;

	GraphInter::get()->display("Enter your new password");

	data = GraphInter::get()->HidePassword();

	GraphInter::get()->checkPassword(data);

	user->setPassword(data);
}

void Session::AliasOptions()
{
	int option;

	do
	{
		GraphInter::get()->clearConsole();

		option = GraphInter::get()->FastName(user->getContactlist());

		if (option == 1)
		{
			AddFastName(this->getUser());
		}
		else if (option != 0)
		{
			if (this->getUser()->getContactlist()->length() == 0)
			{
				GraphInter::get()->display("You have no alias to delete");
				GraphInter::get()->pause();
			}
			else
			{
				if (option == 2)
				{
					if (this->getUser()->getContactlist()->length() > 1)
					{
						std::string name = GraphInter::get()->selectAlias(this);

						if (this->getUser()->getContactlist()->get(name)->alias == "Me")
						{
							GraphInter::get()->display("You cannot delete your self alias");
							GraphInter::get()->pause();
						}
						else
						{
							manager->deleteName(this->getUser(), name);
						}
					}
					else
					{
						GraphInter::get()->display("You cannot delete your self alias");
						GraphInter::get()->pause();
					}
				}
				else if (option == 3)
				{
					if (this->getUser()->getContactlist()->length() > 1)
					{
						int namelenth = this->getUser()->getContactlist()->length();

						for (int i = namelenth - 1; i >= 0; i--)
						{
							if (this->getUser()->getContactlist()->get(this->getUser()->getContactlist()->operator[](i)->user)->alias != "Me")
							{
								this->getUser()->getContactlist()->destroy(this->getUser()->getContactlist()->operator[](i)->getId());
							}
						}
					}
					else
					{
						GraphInter::get()->display("You cannot delete your self alias");
						GraphInter::get()->pause();
					}
				}
			}
		}
	} while (option != 0);
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

	GraphInter::get()->clearConsole();

	if (active_tray()->length() == 0)
	{
		GraphInter::get()->display("You do not have any mail on your active tray");
		GraphInter::get()->pause();
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
	}
}

//If it can, sends the mail to the users who must be sent
void Session::sendMail()
{
	GraphInter::get()->clearConsole();

	Mail* mail = GraphInter::get()->newMail(user->getId(), user->getContactlist());

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

	Mail* forward = GraphInter::get()->forward(originalMail, user->getId(), user->getContactlist());

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

void Session::AddFastName(User* user)
{
	GraphInter::get()->clearConsole();

	if (user->getContactlist()->full())
	{
		GraphInter::get()->display("You cannot asign more alias");
		GraphInter::get()->pause();
	}
	else
	{
		int i, j;
		bool name_right, alias_right;
		std::string idUser, newId;

		do
		{
			name_right = true;

			GraphInter::get()->clearConsole();
			GraphInter::get()->display("Enter the user id you want to asign:");
			GraphInter::get()->enter(idUser);

			if (idUser != "")
			{
				if (manager->getUserList()->get(idUser) == nullptr)
				{
					GraphInter::get()->display("This user does not exist");
					GraphInter::get()->pause();

					name_right = false;
				}
				else if (idUser == user->getId())
				{
					GraphInter::get()->display("There is already an asigned alias for your own username");
					GraphInter::get()->pause();

					name_right = false;
				}
				else
				{
					for (i = 0; i < user->getContactlist()->length() && name_right; i++) {}

					if (i != user->getContactlist()->length())
					{
						GraphInter::get()->display("This username already has an alias asigned");
						GraphInter::get()->pause();

						name_right = false;
					}
				}
			}
		} while (!name_right && idUser != "");

		if (idUser != "")
		{
			do
			{
				std::ostringstream character;
				alias_right = true;

				GraphInter::get()->clearConsole();
				GraphInter::get()->display("User: " + idUser);
				GraphInter::get()->display("Enter the alias you choose for this user (cannot contain '@'):");
				GraphInter::get()->enter(newId);

				if (newId.size() == 0)
				{
					GraphInter::get()->display("Error, the alias cannot be empty");
					GraphInter::get()->pause();

					alias_right = false;
				}
				else if (newId == "Me")
				{
					GraphInter::get()->display("Error, this is a default alias, you cannot asign it");
					GraphInter::get()->pause();

					alias_right = false;
				}
				else
				{
					for (int k = 0; k < newId.size() && alias_right; k++)
					{
						for (int j = 0; j < CENSORED_CHARS; j++)
						{
							if (newId[i] == forbidden[j])
							{
								character << "(" << char(forbidden[j]) << ")";

								GraphInter::get()->display("Error, your id cannot contain the character " + character.str());
								GraphInter::get()->pause();

								alias_right = false;
							}
						}
					}

					for (j = 0; j < user->getContactlist()->length() && alias_right; j++)
					{
						if (newId == user->getContactlist()->operator[](j)->getAlias())
						{
							GraphInter::get()->display("This alias is already asigned to an user");
							GraphInter::get()->pause();

							alias_right = false;
						}
					}
				}
			} while (!alias_right);

			tContact* newContact = new tContact(idUser, newId);

			user->getContactlist()->insert(newContact);
		}
	}
}

