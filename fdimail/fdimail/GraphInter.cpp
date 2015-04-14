#include "GraphInter.h"
#include "Session.h"
#include <iostream>

GraphInter* GraphInter::inter = nullptr;

GraphInter::GraphInter()
{

}

GraphInter::~GraphInter()
{

}

GraphInter* GraphInter::get()
{
	return inter;
}

void GraphInter::load()
{
	if (inter = nullptr) inter = new GraphInter;
}

int GraphInter::drawMail(const Mail* mail, Session* sesion)
{
	std::cout << mail->to_string();

	linea();

	if (sesion->getUser()->getTray() == 0)
	{
		std::cout << "1- Answer" << std::endl
			<< "0- Exit to inbox" << std::endl;

		return digitBetween(0, 1);
	}
	else
	{
		std::cout << "0- Exit to outbox" << std::endl;

		return digitBetween(0, 0);
	}
	
}

User GraphInter::regist(User* user)
{
	int option = logMenu();
	User* newUser = new User;

	std::string id, password;

	do
	{
		if (option == 1)
		{
			newUser->setId(valid_user());

			newUser->setPassword(valid_password());

			return *newUser;
		}
		else if (option == 2)
		{

		}
	} while (option != 0);
}

void GraphInter::drawTraylist(TrayList* list)
{

}

void GraphInter::drawHeader(const Mail* mail)
{

}

void GraphInter::showText(std::string &text)
{

}

int GraphInter::logMenu()
{
	std::cout << "Choose your desired option: " << std::endl
		<< std::setw(3) << "1- Sign up" << std::endl
		<< std::setw(3) << "2- Sign in" << std::endl
		<< std::setw(3) << "0- Exit" << std::endl;

	return digitBetween(0, 2);
}

int GraphInter::mainMenu(Session* sesion)
{
	std::string title = center_word("Inbox", 79);

	std::cout << "Mail of " << (sesion->getUser()->getId()) << std::endl
		<< title << std::endl << "R N" << std::setw(7)
		<< "FROM" << std::setw(29) << "SUBJECT" << std::setw(29)
		<< "DATE" << std::endl << std::endl;

	linea();

	for (int i = 0; i < sesion->getUser()->active_tray()->lenght(); i++)
	{
		if ((*(sesion->getUser()->active_tray()))[i]->read)
		{
			std::cout << "*";
		}

		std::string id = (*(sesion->getUser()->active_tray()))[i]->idMail;

		std::string thisMail = sesion->getManager()->getMailList().get(id)->header();

		std::cout << std::setw(3) << (i + 1) 
			<< " - " << thisMail << std::endl;
	}

	linea();

	std::cout << "Choose your desired option: " << std::endl
		<< std::setw(3) << "1- Read mail" << std::endl
		<< std::setw(3) << "2- Send mail" << std::endl
		<< std::setw(3) << "3- Delete mail" << std::endl;

	if (sesion->getUser()->getTray() == 0)
	{
		std::cout << std::setw(3) << "4- See outbox" << std::endl;
	}
	else
	{
		std::cout << std::setw(3) << "4- See iutbox" << std::endl;
	}
	std::cout << std::setw(3) << "5- fast read of unread mails" << std::endl
		<< std::setw(3) << "0- Sign out" << std::endl;

	linea();

	std::cout << "Enter an option:" << std::endl;

	return digitBetween(0, 5);
}

bool GraphInter::mailMenu()
{
	return false;//Placeholder
}

std::string GraphInter::inputBox(std::string &message)
{
	return "";//Placeholder
}

std::string GraphInter::selectMail(TrayList* tray)
{
	return "";//Placeholder
}

void GraphInter::pause()
{
	std::cin.sync();
	std::cin.get();
}

//It asks you for a digit, and makes sure that digit
//is between the other two that it has as arguments
int GraphInter::digitBetween(int a, int b)
{
	int digit = -1;

	do
	{
		std::cin.sync(); //Por si quedan datos basura en el buffer
		std::cin >> digit;

		if (std::cin.fail())
		{
			std::cout << "Error, enter a digit" << std::endl;
			std::cin.clear();
		}

		else if (digit < a || digit > b)
		{
			std::cout << "Error, enter a digit between " << a << " and " << b << std::endl;
			digit = -1;
		}

	} while (digit == -1);

	return digit;
}

std::string GraphInter::center_word(std::string word, int lenght)
{
	if (word.size() == lenght) return word;

	else
	{
		for (int i = word.size(); i < lenght; i++)
		{
			if (word.size() % 2 == 0)
			{
				word = word + "-";
			}
			else if (word.size() % 2 == 1)
			{
				word = "-" + word;
			}
		}
		return word;
	}
}

void GraphInter::linea()
{
	std::cout << std::setfill('-')
		<< std::setw(79) << '-'
		<< std::endl << std::setfill(' ');
}

std::string GraphInter::valid_user()
{
	std::string id;

	std::cout << "Choose your id: " << std::endl;

	std::cin >> id;

	for (int i = 0; i < id.size(); i++)
	{
		if (id[i] == ' ')
		{
			std::cout << "Error, your id cannot contain a space" << std::endl;

			std::cin >> id;
		}
	}

	while (id.size() > 15)
	{
		std::cout << "Error, your id cannot be longer than 15 characters " << std::endl;

		std::cin >> id;
	}

	id = id + "@fdimail.com";

	return id;
}

std::string check_user()
{
	std::string id;

	std::cout << "Enter your id:" << std::endl;

	std::cin >> id;


}

std::string GraphInter::valid_password()
{
	std::string password, second_password;

	std::cout << "Choose your password:" << std::endl;

	std::cin >> password;

	std::cout << "Confirm your password:" << std::endl;

	std::cin >> second_password;

	while (second_password != password)
	{
		std::cout << "Error, you must repeat your first password" << std::endl
			<< "Confirm your password:" << std::endl;

		std::cin >> second_password;
	}

	return password;
}