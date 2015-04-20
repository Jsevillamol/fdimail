#include "GraphInter.h"
#include "Session.h"
#include <iostream>

GraphInter* GraphInter::inter = nullptr;

GraphInter::GraphInter() {}

GraphInter::~GraphInter() {}

GraphInter* GraphInter::get()
{
	return inter;
}

void GraphInter::load()
{
	if (inter == nullptr) inter = new GraphInter;
}

int GraphInter::mainMenu()
{
	std::cout << "Choose your desired option: " << std::endl
		<< std::setw(3) << "1- Sign up" << std::endl
		<< std::setw(3) << "2- Sign in" << std::endl
		<< std::setw(3) << "0- Exit" << std::endl;

	return digitBetween(0, 2);
}

void GraphInter::logMenu(std::string &username, std::string &password)
{
	username = valid_user();

	std::cout << "Enter password:" << std::endl;

	std::cin.sync();
	std::cin >> password;
	std::cin.clear();
}

int GraphInter::sessionMenu(Session* sesion)
{
	std::string title;

	std::cout << "Mail of " << (sesion->getUser()->getId()) << std::endl;

	if (sesion->getUser()->getTray() == 0)
	{
		title = center_word("Inbox", 79);
	}
	else if (sesion->getUser()->getTray() != 0)
	{
		title = center_word("Outbox", 79);
	}

	std::cout << title << std::endl << "R N" << std::setw(7)
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
	else if (sesion->getUser()->getTray() != 0)
	{
		std::cout << std::setw(3) << "4- See inbox" << std::endl;
	}
	std::cout << std::setw(3) << "5- fast read of unread mails" << std::endl
		<< std::setw(3) << "0- Sign out" << std::endl;

	linea();

	std::cout << "Enter an option:" << std::endl;

	return digitBetween(0, 5);
}

std::string GraphInter::selectMail(Session* sesion)
{
	int number;

	std::cout << "Enter the number of the mail you choose:" << std::endl;

	number = digitBetween(1, sesion->getUser()->active_tray()->lenght());

	return (*(sesion->getUser()->active_tray()))[number-1]->idMail;
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

Mail* GraphInter::newMail(const std::string &sender)
{
	std::ostringstream ID;
	Mail* mail = new Mail;

	mail->from = sender;
	mail->date = time(0);

	ID << sender << "_" << mail->date;
	mail->id = ID.str();

	std::cout << "From: " << sender << std::endl;

	std::cout << "To: ";
	std::cin >> mail->to;

	std::cout << "Subject: ";
	std::cin >> mail->subject;

	std::cout << "Body: ";
	std::getline(std::cin, mail->body, '#');

	return mail;
}

Mail* GraphInter::answerMail(Mail &originalMail)
{
	Mail* mail = new Mail;
	std::ostringstream ID, BODY, SUBJECT;
	std::string WhatToSay;

	SUBJECT << "Re: " << originalMail.subject;

	mail->from = originalMail.to;
	mail->date = time(0);
	mail->to = originalMail.from;
	mail->subject = SUBJECT.str();


	ID << originalMail.to << "_" << mail->date;
	mail->id = ID.str();



	std::cout << "From: " << originalMail.to << std::endl;

	std::cout << "To: ";
	mail->to = originalMail.from;

	std::cout << "Subject: ";
	std::cin >> mail->subject;

	std::cout << "Body: ";
	std::cin >> WhatToSay;

	BODY << WhatToSay << std::endl << std::endl
		<< originalMail.to_string();//ultimo mail;

	mail->body = BODY.str();

	return mail;
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

	std::cout << "Enter your id: " << std::endl;

	std::cin.sync();
	std::cin >> id;
	std::cin.clear();

	for (int i = 0; i < id.size(); i++)
	{
		if (id[i] == ' ')
		{
			std::cout << "Error, your id cannot contain a space" << std::endl
				<< "Enter your id: " << std::endl;

			std::cin.sync();
			std::cin >> id;
			std::cin.clear();
		}
		if (id.size() > 15)
		{
			std::cout << "Error, your id cannot be longer than 15 characters " << std::endl
				<< "Enter your id: " << std::endl;

			std::cin.sync();
			std::cin >> id;
			std::cin.clear();
		}
	}

	id = id + "@fdimail.com";

	return id;
}

void GraphInter::drawMail(const Mail* mail)
{
	std::cout << mail->to_string();
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

		std::cout << "Confirm your password:" << std::endl;

		std::cin >> newPassword;
	}

	return password;
}

