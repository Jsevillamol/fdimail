#include "GraphInter.h"
#include "Session.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <assert.h>

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
	error("Choose your desired option: ");
	tab_word("1- Sign up");
	tab_word("2- Sign in");
	tab_word("0- Exit");

	linea();

	error("Enter an option:");

	return digitBetween(0, 2);
}

void GraphInter::logMenu(std::string &username, std::string &password)
{
	username = valid_user();

	error("Enter password:");

	enter(password);
}

int GraphInter::sessionMenu(Session* session)
{
	std::string title;
	std::ostringstream menu;

	std::cout << "Mail of " << (session->getUser()->getId()) << std::endl;

	if (session->active_list)
	{
		title = center_word("Outbox", HORIZONTAL, "-");
	}
	else
	{
		title = center_word("Inbox", HORIZONTAL, "-");
	}

	menu << title << "\n" << "R N" << std::setw(7)
		<< "FROM" << std::setw(33) << "SUBJECT" << std::setw(31)
		<< "DATE" << std::endl;

	error(menu.str());

	linea();

	if (session->active_tray()->lenght() == 0)
	{
		error(center_word("You have no mails", HORIZONTAL, " "));
	}
	else
	{
		for (int i = session->active_tray()->lenght()-1; i >= 0; i--)
		{
			if (session->active_tray()->operator[](i)->read)
			{
				error(" ");
			}
			else error("*");

			std::string id = session->active_tray()->operator[](i)->idMail;

			/*std::cout << "Id of mail to show in main menu: " << id << std::endl;
			std::cout << "Id of session: " << id << std::endl;
			std::cout << "MailList direction: " << (session->getManager()->getMailList()) << std::endl;*/
			//std::cout << "Id: " << id << std::endl;
			Mail* mail = session->getManager()->getMailList()->get(id);

			//std::cout << "Dir of mail: " << mail << std::endl;
			assert(mail != nullptr);
			std::string thisMail = mail->header();
			std::ostringstream show;

			show << std::setw(3) << (session->active_tray()->lenght() - i) << " - " << thisMail;
			error(show.str());
		}
	}
	linea();

	error("Choose your desired option: ");
	tab_word("1- Read mail");
	tab_word("2- Send mail");
	tab_word("3- Delete mail");

	if (session->active_list)
	{
		tab_word("4- See inbox");
	}
	else
	{
		tab_word("4- See outbox");
	}
	tab_word("5- fast read of unread mails");
	tab_word("0- Sign out");

	linea();

	std::cout << "Enter an option:" << std::endl;

	return digitBetween(0, 5);
}

int GraphInter::WhatToDelete()
{
	tab_word("1- Choose mail");
	tab_word("0- Delete all mails");

	linea();

	error("Enter an option:");

	return digitBetween(0, 1);
}

std::string GraphInter::selectMail(Session* session)
{
	int number;

	error("Enter the number of the mail you choose:");

	number = digitBetween(1, session->active_tray()->lenght());

	return (*(session->active_tray()))[number-1]->idMail;
}

int GraphInter::mailMenu()
{
	error("Choose an option:");
	tab_word("1- Answer");
	tab_word("2- Forward");
	tab_word("0- Exit to sesion menu");

	linea();

	error("Enter an option:");

	return digitBetween(0, 2);
}

Mail* GraphInter::newMail(const std::string &sender)
{
	std::ostringstream ID;
	Mail* mail = new Mail;
	int i;

	mail->from = sender;
	mail->date = time(0);
	mail->user_count = 2;

	ID << sender << "_" << mail->date;
	mail->id = ID.str();

	error("From: " + sender);

	error("How many recipients do you want this mail to be sent?");
	mail->recipient_count = digitBetween(0, MAX_RECIPIENTS);

	for (i = 0; i < mail->recipient_count; i++)
	{
		if (i == 0)
		{
			error("To: ");
		}
		else
		{
			error("CC: ");
		}
		std::cin.ignore();
		enter(mail->recipients[i]);

		if (mail->recipients[i] == "")
		{
			mail->recipient_count--;
			i--;
		}
		else
		{
			for (int j = 0; j <= i; j++)
			{
				for (int k = 0; k <= i; k++)
				{
					if (k != j && mail->recipients[j] == mail->recipients[k])
					{
						error("You have already choose this destinatary, you cannot choose it again");
					}
				}
			}
		}
	}

	if (mail->recipient_count == 0)
	{
		delete mail;
		return nullptr;
	}
	else
	{
		mail->user_count = mail->recipient_count + 1;

		error("Subject: ");
		enter(mail->subject);

		if (mail->subject == "")
		{
			mail->subject = "No subject";
		}

		error("Body (enter twice (ENTER) to end the body): ");

		std::string line;
		mail->body = "";
		do{
			enter(line);
			mail->body += line;
		} while (line != "");

		if (mail->body == "")
		{
			delete mail;
			return nullptr;
		}
		else return mail;
	}
}

Mail* GraphInter::answerMail(Mail* &originalMail, const std::string &sender)
{
	Mail* mail = new Mail;
	std::ostringstream ID, BODY, SUBJECT;
	std::string WhatToSay;

	SUBJECT << "Re: " << originalMail->subject;

	mail->from = sender;
	mail->date = time(0);

	mail->recipient_count = 1;
	mail->recipients[0] = originalMail->from;
	mail->subject = SUBJECT.str();

	ID << sender << "_" << mail->date;
	mail->id = ID.str();

	error(center_word("Answered mail", HORIZONTAL, " "));

	error("");

	error("From: " + sender);

	error("To: " + originalMail->from);

	error("Subject: " + mail->subject);

	error("Body (enter twice (ENTER) to end the body): ");
	
	std::string line;
	WhatToSay = "";
	do{
		enter(line);
		WhatToSay += line;
	} while (line != "");

	if (WhatToSay == "")
	{
		WhatToSay = "No body";
	}

	BODY << WhatToSay << std::endl << linea()
		<< std::endl << originalMail->to_string();//ultimo mail;

	mail->body = BODY.str();

	return mail;
}

Mail* GraphInter::forward(Mail* &originalMail, const std::string &sender)
{
	int i;
	Mail* mail = new Mail;
	std::ostringstream ID, BODY, SUBJECT;
	std::string WhatToSay;

	SUBJECT << "Re: " << originalMail->subject;

	mail->from = sender;
	mail->date = time(0);
	mail->subject = SUBJECT.str();

	ID << sender << "_" << mail->date;
	mail->id = ID.str();

	error(center_word("Forwarded mail", HORIZONTAL, " "));

	error("");

	error("From: " + sender);

	error("How many recipients do you want this mail to be sent?");
	mail->recipient_count = digitBetween(0, MAX_RECIPIENTS);

	for (i = 0; i < mail->recipient_count && mail->recipients[i] != ""; i++)
	{
		if (i == 0)
		{
			error("To: ");
		}
		else
		{
			error("CC: ");
		}
		std::cin.ignore();
		enter(mail->recipients[i]);

		if (mail->recipients[i] == "")
		{
			mail->recipient_count--;
			i--;
		}
		else
		{
			for (int j = 0; j <= i; j++)
			{
				for (int k = 0; k <= i; k++)
				{
					if (k != j && mail->recipients[j] == mail->recipients[k])
					{
						error("You have already choose this destinatary, you cannot choose it again");
					}
				}
			}
		}
	}
	
	if (mail->recipient_count == 0)
	{
		delete mail;
		return nullptr;
	}
	else
	{
		mail->user_count = mail->recipient_count + 1;

		error("Subject: " + mail->subject);

		error("Body (enter twice (ENTER) to end the body): ");

		std::string line;
		WhatToSay = "";
		do{
			enter(line);
			WhatToSay += line;
		} while (line != "");

		if (WhatToSay == "")
		{
			WhatToSay = "No body";
		}

		BODY << WhatToSay << std::endl << linea()
			<< std::endl << originalMail->to_string();//ultimo mail;

		mail->body = BODY.str();

		return mail;
	}
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
		enter(digit);

		if (std::cin.fail())
		{
			error("Error, enter a digit");
		}

		else if (digit < a || digit > b)
		{
			error("Error, enter a digit between " + std::to_string(a) + " and " + std::to_string(b));
			digit = -1;
		}

	} while (digit == -1);

	return digit;
}

std::string GraphInter::center_word(std::string word, int lenght, std::string arround)
{
	if (word.size() != lenght)
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
	}
	word = word + "\n";

	return word;
}

void GraphInter::tab_word(std::string word)
{
	std::ostringstream tab;

	tab << std::setw(2 + word.size()) << word;

	error(tab.str());
}

std::string GraphInter::linea()
{
	std::ostringstream line;

	line << std::setfill('-')
		<< std::setw(79) << '-'
		<< std::endl << std::setfill(' ');

	return line.str();
}

std::string GraphInter::valid_user()
{
	std::string id;
	bool id_right;

	error("Enter your id: ");

	do
	{
		id_right = true;

		enter(id);

		if (id.size() > 15)
		{
			error("Error, your id cannot be longer than 15 characters ");
			error("Enter your id: ");

			id_right = false;
		}
		else
		{
			for (int i = 0; i < int(id.size()) && id_right; i++)
			{
				if (id[i] == ' ')
				{
					error("Error, your id cannot contain a space");
					error("Enter your id: ");

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
		error("Error, the passwords are not the same");
		error("Enter your password:");

		enter(password);

		error("Confirm your password:");

		enter(newPassword);
	}
}

void GraphInter::clearConsole(){ system("cls"); }

void GraphInter::error(std::string error)
{
	std::cout << error << std::endl;
}

void GraphInter::enter(std::string &word)
{
	std::cin.sync();
	std::getline(std::cin, word);
	std::cin.clear();
}

void GraphInter::enter(int &digit)
{
	std::cin.sync();
	std::cin >> digit;
	std::cin.clear();
}