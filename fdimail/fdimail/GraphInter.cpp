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

/*int GraphInter::drawMail(const Mail* mail, Session* sesion)
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
}*/


/*int mainMenu(); //Options: sign in and sign up
void logMenu(std::string &username, std::string &password); //Returns username and password
int sessionMenu(Session* sesion); //Shows active tray, returns user options (read mail, delete mail, etc)
std::string selectMail(TrayList* tray); //Shows active tray, returns idMail of mail selected
bool mailMenu(); //Shows mail, returns options answer (true) or return to sessionMenu (false)
Mail newMail(std::string &sender); //Returns a full mail
Mail answerMail(Mail &originalMail);*/

int GraphInter::mainMenu()
{
	std::cout << "Choose your desired option: " << std::endl
		<< std::setw(3) << "1- Sign up" << std::endl
		<< std::setw(3) << "2- Sign in" << std::endl
		<< std::setw(3) << "0- Exit" << std::endl;

	return digitBetween(0, 2);


}

int GraphInter::logMenu(std::string &username, std::string &password)
{
	int option;

	option = mainMenu();

	if (option != 0)
	{
		username = valid_user();

		std::cout << "Enter password:" << std::endl;

		std::cin >> password;
	}
	
	return option;
}

int GraphInter::sessionMenu(Session* sesion)
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
	int option;

	std::cout << "Choose an option:" << std::endl
		<< "1- Answer" << std::endl
		<< "0- Exit to sesion menu" << std::endl;

	option = digitBetween(0, 1);

	if (option == 1) return true;

	else return false;
}

Mail GraphInter::newMail(std::string &sender)
{
	MailList list;

	Mail* newMail;

	newMail = list.get(sender);

	return *newMail;
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

void GraphInter::drawMail(const Mail* mail)
{
	std::cout << mail->to_string();
}

void GraphInter::drawTraylist(TrayList* list)
{
	/*std::string title = center_word("Inbox", 79);

	std::cout << "Mail of " << () << std::endl
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
			<< " - " << thisMail << std::endl;*/
}

std::string GraphInter::check_password(std::string password)
{
	std::string newPassword;

	std::cout << "Confirm your password: " << std::endl;

	std::cin >> newPassword;

	while (newPassword != password)
	{
		std::cout << "Error, te passwords are not the same" << std::endl
			<< "Enter your password:" << std::endl;

		std::cin >> password;

		std::cout << "Repeat your password:" << std::endl;

		std::cin >> newPassword;
	}

	return password;
}

