#include "GraphInter.h"
#include "Session.h"
#include <iostream>
#include <iomanip>

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

void GraphInter::close()
{
	if (inter != nullptr) delete inter;
}

int GraphInter::mainMenu()
{
	std::cout << "Choose your desired option: " << std::endl
		<< tab_word("1- Sign up")
		<< tab_word("2- Sign in")
		<< tab_word("0- Exit");

	linea();

	std::cout << "Enter an option:" << std::endl;

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

int GraphInter::sessionMenu(Session* session)
{
	std::string title;

	std::cout << "Mail of " << (session->getUser()->getId()) << std::endl;

	if (session->active_list)
	{
		title = center_word("Outbox", HORIZONTAL, "-");
	}
	else
	{
		title = center_word("Inbox", HORIZONTAL, "-");
	}

	std::cout << title << std::endl << "R N" << std::setw(7)
		<< "FROM" << std::setw(33) << "SUBJECT" << std::setw(31)
		<< "DATE" << std::endl << std::endl;

	linea();

	if (session->active_tray()->lenght() == 0)
	{
		std::cout << center_word("You have no mails", HORIZONTAL, " ");
	}
	else
	{
		for (int i = 0; i < session->active_tray()->lenght(); i++)
		{
			if (session->active_tray()->operator[](i)->read)
			{
				std::cout << ' ';
			}
			else std::cout << '*';

			std::string id = session->active_tray()->operator[](i)->idMail;

			/*std::cout << "Id of mail to show in main menu: " << id << std::endl;
			std::cout << "Id of session: " << id << std::endl;
			std::cout << "MailList direction: " << (sesion->getManager()->getMailList()) << std::endl;*/

			Mail * mail = session->getManager()->getMailList()->get(id);

			//std::cout << "Dir of mail: " << mail << std::endl;
			assert(mail != nullptr);
			std::string thisMail = mail->header();

			std::cout << std::setw(2) << (i + 1)
				<< " - " << thisMail << std::endl;
		}
	}
	linea();

	std::cout << "Choose your desired option: " << std::endl
		<< tab_word("1- Read mail")
		<< tab_word("2- Send mail")
		<< tab_word("3- Delete mail");

	if (session->active_list)
	{
		std::cout << tab_word("4- See inbox");
	}
	else
	{
		std::cout << tab_word("4- See outbox");
	}
	std::cout << tab_word("5- fast read of unread mails")
		<< tab_word("0- Sign out");

	linea();

	std::cout << "Enter an option:" << std::endl;

	return digitBetween(0, 5);
}

int GraphInter::WhatToDelete()
{
	std::cout << tab_word("1- Choose mail")
		<< tab_word("0- Delete all mails");

	linea();

	std::cout << "Enter an option:" << std::endl;

	return digitBetween(0, 1);
}

std::string GraphInter::selectMail(Session* session)
{
	int number;

	std::cout << "Enter the number of the mail you choose:" << std::endl;

	number = digitBetween(1, session->active_tray()->lenght());

	return (*(session->active_tray()))[number-1]->idMail;
}

int GraphInter::mailMenu()
{
	std::cout << "Choose an option:" << std::endl
		<< tab_word("1- Answer")
		<< tab_word("2- Forward")
		<< tab_word("0- Exit to sesion menu");

	linea();

	std::cout << "Enter an option:" << std::endl;

	return digitBetween(0, 2);
}

Mail* GraphInter::newMail(const std::string &sender)
{
	std::ostringstream ID;
	Mail* mail = new Mail;

	mail->from = sender;
	mail->date = time(0);
	mail->user_count = 2;

	ID << sender << "_" << mail->date;
	mail->id = ID.str();

	std::cout << "From: " << sender << std::endl;

	std::cout << "To: ";
	std::cin.ignore();
	std::getline(std::cin, mail->to);

	std::cout << "Subject: ";
	std::cin.ignore();
	getline(std::cin, mail->subject);

	std::cout << "Body (enter '#' and (ENTER) to end the body): " << std::endl;
	std::getline(std::cin, mail->body, '#');

	if (mail->body == "" || mail->from == "" || mail->to == "" || mail->subject == "")
	{
		delete mail;
		return nullptr;
	}
	else return mail;
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

	std::cout << "To: " << originalMail.from << std::endl;

	std::cout << "Subject: " << mail->subject << std::endl;

	std::cout << "Body (enter '#' and (ENTER) to end the body): " << std::endl;
	std::getline(std::cin, WhatToSay, '#');

	BODY << WhatToSay << std::endl << std::endl
		<< originalMail.to_string();//ultimo mail;

	mail->body = BODY.str();

	if (mail->body == "" || mail->from == "" || mail->to == "" || mail->subject == "")
	{
		delete mail;
		return nullptr;
	}
	else return mail;
}

Mail* GraphInter::forward(Mail &originalMail)
{
	Mail* mail = new Mail;
	std::ostringstream ID, BODY, SUBJECT;
	std::string WhatToSay;

	SUBJECT << "Re: " << originalMail.subject;

	mail->from = originalMail.to;
	mail->date = time(0);
	mail->subject = SUBJECT.str();

	ID << originalMail.to << "_" << mail->date;
	mail->id = ID.str();

	std::cout << "From: " << originalMail.to << std::endl;

	std::cout << "To: ";
	std::getline(std::cin, mail->to);

	std::cout << "Subject: " << mail->subject << std::endl;

	std::cout << "Body (enter '#' and (ENTER) to end the body): " << std::endl;
	std::getline(std::cin, WhatToSay, '#');

	BODY << WhatToSay << std::endl << std::endl
		<< originalMail.to_string();//ultimo mail;

	mail->body = BODY.str();

	if (mail->body == "" || mail->from == "" || mail->to == "" || mail->subject == "")
	{
		delete mail;
		return nullptr;
	}
	else return mail;
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

std::string GraphInter::center_word(std::string word, int lenght, std::string arround)
{
	if (word.size() == lenght) return word;

	else
	{
		for (int i = word.size(); i < lenght; i++)
		{
			if (word.size() % 2 == 0)
			{
				word = word + arround;
			}
			else if (word.size() % 2 == 1)
			{
				word = arround + word;
			}
		}
		word = word + "\n";

		return word;
	}
}

std::string GraphInter::tab_word(std::string word)
{
	std::ostringstream tab;

	tab << std::setw(2 + word.size()) << word << std::endl;

	return tab.str();
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
	bool id_right;

	std::cout << "Enter your id: " << std::endl;

	do
	{
		id_right = true;

		std::cin.sync();
		std::getline(std::cin, id);
		std::cin.clear();

		if (id.size() > 15)
		{
			std::cout << "Error, your id cannot be longer than 15 characters " << std::endl
				<< "Enter your id: " << std::endl;

			id_right = false;
		}
		else
		{
			for (int i = 0; i < id.size() && id_right; i++)
			{
				if (id[i] == ' ')
				{
					std::cout << "Error, your id cannot contain a space" << std::endl
						<< "Enter your id: " << std::endl;

					id_right = false;
				}
			}
		}		
	} while (!id_right);

	id = id + "@fdimail.com";

	return id;
}

void GraphInter::drawMail(const Mail* mail)
{
	std::cout << mail->to_string() << std::endl;
}

void GraphInter::check_password(std::string& password)
{
	std::string newPassword;

	std::cout << "Confirm your password: " << std::endl;

	std::cin >> newPassword;

	while (newPassword != password)
	{
		std::cout << "Error, the passwords are not the same" << std::endl
			<< "Enter your password:" << std::endl;

		std::cin >> password;

		std::cout << "Confirm your password:" << std::endl;

		std::cin >> newPassword;
	}
}

void GraphInter::error(const char error[])
{
	std::cout << error << std::endl;
}