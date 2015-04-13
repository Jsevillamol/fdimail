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

void GraphInter::drawMail(const Mail* mail)
{

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

	if (sesion->getUser()->active_tray() == 0)
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