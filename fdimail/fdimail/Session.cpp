#include "Session.h"
#include "GraphInter.h"
#include "Mail.h"

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
	visible.init(active_tray());
	Filter filter = none;
	int opt;

	do{
		GraphInter::get()->clearConsole();
		visible.refresh();
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
			visible.link(active_tray());
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
		case 8:
			filterOptions(filter);
			break;
		}
	} while (opt != 0);
	visible.link(nullptr);
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
		GraphInter::get()->clearConsole();

		GraphInter::get()->showTray(this);
		//Display mail
		Mail* mail = GraphInter::get()->selectMail(this);
		GraphInter::get()->drawMail(mail);
		//Change mail status to read
		active_tray()->readMail(mail->getId());

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
	int option;

	if (visible.length() == 0)
	{
		GraphInter::get()->display("Error, you have no mails to delete");
		GraphInter::get()->pause();
		GraphInter::get()->clearConsole();

	}
	else
	{
		do
		{
			option = 0;

			visible.refresh();
			GraphInter::get()->clearConsole();
			GraphInter::get()->showTray(this);

			if (visible.length() != 0)
			{
				option = GraphInter::get()->WhatToDelete();

				if (option == 1)
				{
					//Select mail
					std::string id = GraphInter::get()->selectMail(this)->getId();
					//Delete
					manager->deleteMail(active_tray(), id);
					GraphInter::get()->clearConsole();
				}
				else if (option == 2)
				{
					for (int i = 0; i < visible.length(); i++)
					{
						std::string newId = (*(this->active_tray()))[0]->getId();

						manager->deleteMail(active_tray(), newId);
					}
				}
			}
		} while (visible.length() != 0 && option != 0);
	}
}

//It shows you all the mails that you did not
//read from your input box
void Session::fastRead()
{

	GraphInter::get()->clearConsole();

	if (get_visible()->length() == 0)
	{
		GraphInter::get()->display("You do not have any mail on your active tray");
		GraphInter::get()->pause();
	}
	else
	{
		visible.filterByRead(false);
		visible.orderByDate();
		visible.orderBySubject();
		if (visible.length() > 0)
		{
			for (int i = 0; i < visible.length(); i++)
			{
				//Display mail
				GraphInter::get()->drawMail(visible[i]->mail);
				GraphInter::get()->pause();

				//Change mail status to read
				visible[i]->read = true;
			}
		}
		else
		{
			GraphInter::get()->display("You do not have any unread mail");
			GraphInter::get()->pause();
		}
	}
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
					for (i = 0; i < user->getContactlist()->length() && name_right; i++)
					{
						if (idUser == user->getContactlist()->operator[](i)->user)
						{
							GraphInter::get()->display("This username already has an alias asigned");
							GraphInter::get()->pause();

							name_right = false;
						}
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
							if (newId[k] == forbidden[j])
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
						if (newId == user->getContactlist()->operator[](j)->getId())
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
							this->getUser()->getContactlist()->destroy(name);
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

void Session::filterOptions(Filter filter)
{
	int option;

	GraphInter::get()->clearConsole();

	option = GraphInter::get()->filter();

	if (option == 1)
	{
		chooseOrder(filter);
	}
	else if (option == 2)
	{
		chooseFilter(filter);
	}
	else if (option == 3)
	{
		this->get_visible()->closeFilter();
	}
}

void Session::chooseFilter(Filter filter)
{
	this->get_visible()->closeFilter();

	GraphInter::get()->choose("filter", filter, this);

	if (filter != none)
	{
		if (filter == date)
		{
			char* lowdate = new char[256];
			char* update  = new char[256];

			GraphInter::get()->display("Enter the lower date");
			GraphInter::get()->enter(lowdate);
			GraphInter::get()->display("Enter the upper date");
			GraphInter::get()->enter(update);

			this->get_visible()->setFilterDate(lowdate, update);
		}
		else if (filter == read)
		{
			this->get_visible()->setFilterRead();
		}
		else if (filter == unread)
		{
			this->get_visible()->setFilterUnread();
		}
		else
		{
			std::string reference;

			GraphInter::get()->display("Enter your reference word");
			GraphInter::get()->enter(reference);

			this->get_visible()->setFilter(reference, filter);
		}
	}
}

void Session::chooseOrder(Filter filter)
{
	GraphInter::get()->choose("order", filter, this);

	this->get_visible()->changeOrder(filter);
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

	manager->getUserList()->pop(user);

	user->setId(data);
	user->getContactlist()->changeMe(std::string(data));
	manager->getUserList()->insert(user);
}

//Allow you to change your password
void Session::changePassword()
{
	std::string data;

	GraphInter::get()->display("Enter your new password");

	data = GraphInter::get()->HidePassword();

	GraphInter::get()->display("");
	GraphInter::get()->checkPassword(data);

	user->setPassword(data);
}