#include "GraphInter.h"
#include "Session.h"
#include <sstream>
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

//Options: sign in and sign up
int GraphInter::mainMenu()
{
	display("Choose your desired option: ");
	tab_word("1- Sign up");
	tab_word("2- Sign in");
	tab_word("0- Exit");

	display(linea());

	display("Enter an option:");

	return digitBetween(0, 2);
}

//Returns username and password
void GraphInter::logMenu(std::string &username, std::string &password)
{
	username = valid_user();

	display("Enter password:");

	enter(password);
}

//Shows active tray, returns user options (read mail, delete mail, etc)
int GraphInter::sessionMenu(Session* session)
{
	std::string title, thisMail;
	std::ostringstream menu;

	display("Mail of " + session->getUser()->getId());

	if (session->active_list)
	{
		title = center_word("Outbox", HORIZONTAL, "-");
	}
	else
	{
		title = center_word("Inbox", HORIZONTAL, "-");
	}

	display(linea());

	menu << title << "\n" << "R N" << std::setw(7)
		<< "FROM" << std::setw(33) << "SUBJECT" << std::setw(31)
		<< "DATE" << std::endl;

	display(menu.str());

	display(linea());

	if (session->active_tray()->length() == 0)
	{
		display(center_word("You have no mails", HORIZONTAL, " "));
	}
	else
	{
		for (int i = session->active_tray()->length()-1; i >= 0; i--)
		{
			std::ostringstream show;

			if (!session->active_tray()->operator[](i)->read)
			{
				show << "*";
			}
			else
			{
				show << " ";
			}

			std::string id = session->active_tray()->operator[](i)->idMail;

			Mail* mail = session->getManager()->getMailList()->get(id);

			if (mail == nullptr)
			{
				mail = errorMail(session->getUser()->getId());
			}
	
			thisMail = mail->header();

			show << std::setw(2) << (session->active_tray()->length() - i) << " - " << thisMail;
			display(show.str());
		}
	}
	display(linea());

	display("Choose your desired option: ");
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
	tab_word("5- Fast read of unread mails");
	tab_word("6- Account options");
	tab_word("0- Sign out");

	display(linea());

	display("Enter an option:");

	return digitBetween(0, 6);
}

//Little options menu
int GraphInter::WhatToDelete()
{
	display(linea());

	tab_word("1- Choose mail");
	tab_word("0- Delete all mails");

	display(linea());

	display("Enter an option:");

	return digitBetween(0, 1);
}

//Little options menu
int GraphInter::AccountOptions()
{
	display(linea());

	tab_word("1- Change username");
	tab_word("2- Change password");
	tab_word("3- Delete account");
	tab_word("0- Exit to session menu");

	display(linea());

	display("Enter an option:");

	return digitBetween(0, 3);
}

//Shows active tray, returns idMail of mail selected
std::string GraphInter::selectMail(Session* session)
{
	int number;

	display("Enter the number of the mail you choose:");

	number = digitBetween(1, session->active_tray()->length());

	return (*(session->active_tray()))[number-1]->idMail;
}

//Shows mail, returns options answer, forward, or return to sessionMenu
int GraphInter::mailMenu()
{
	display("Choose an option:");
	tab_word("1- Answer");
	tab_word("2- Forward");
	tab_word("0- Exit to sesion menu");

	display(linea());

	display("Enter an option:");

	return digitBetween(0, 2);
}

//Returns a full mail
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

	display("From: " + sender);

	display("How many recipients do you want this mail to be sent?");
	mail->recipient_count = digitBetween(0, MAX_RECIPIENTS);

	for (i = 0; i < mail->recipient_count; i++)
	{
		if (i == 0)
		{
			display("To ('Me' for send it to yourself): ");
		}
		else
		{
			display("CC ('Me' for send it to yourself): ");
		}
		std::cin.ignore();
		enter(mail->recipients[i]);

		if (mail->recipients[i] == "Me")
		{
			mail->recipients[i] = sender;
		}
		if (mail->recipients[i] == "")
		{
			mail->recipient_count--;
			i--;
		}
		else
		{
			for (int j = 0; j <= i; j++)
			{
				if (i != j && mail->recipients[j] == mail->recipients[i])
				{
					display("You have already choose this destinatary, you cannot choose it again");

					i--;
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

		display("Subject: ");
		enter(mail->subject);

		if (mail->subject == "")
		{
			mail->subject = "No subject";
		}

		display("Body (enter twice (ENTER) to end the body): ");

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

//Returns an answer mail
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
	display(center_word("Answered mail", HORIZONTAL, " "));

	display("");

	display("From: " + sender);

	display("To: " + originalMail->from);

	display("Subject: " + mail->subject);

	display("Body (enter twice (ENTER) to end the body): ");
	
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

//Returns a forward mail
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

	display(center_word("Forwarded mail", HORIZONTAL, " "));

	display("");

	display("From: " + sender);

	display("How many recipients do you want this mail to be sent?");
	mail->recipient_count = digitBetween(0, MAX_RECIPIENTS);

	for (i = 0; i < mail->recipient_count && mail->recipients[i] != ""; i++)
	{
		if (i == 0)
		{
			display("To ('Me' for send it to yourself): ");
		}
		else
		{
			display("CC ('Me' for send it to yourself): ");
		}
		std::cin.ignore();
		enter(mail->recipients[i]);

		if (mail->recipients[i] == "Me")
		{
			mail->recipients[i] = sender;
		}
		if (mail->recipients[i] == "")
		{
			mail->recipient_count--;
			i--;
		}
		else
		{
			for (int j = 0; j <= i; j++)
			{
				if (i != j && mail->recipients[j] == mail->recipients[i])
				{
					display("You have already choose this destinatary, you cannot choose it again");

					i--;
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

		display("Subject: " + mail->subject);

		display("Body (enter twice (ENTER) to end the body): ");

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

//Returns a default mail, which is sent when one of the 
//user active tray mails does not exist
Mail* GraphInter::errorMail(const std::string &sender)
{
	std::ostringstream ID;
	Mail* mail = new Mail;

	mail->from = "Tecnical Service";
	mail->date = time(0);
	mail->user_count = 2;

	ID << sender << "_" << mail->date;
	mail->id = ID.str();

	mail->recipient_count = 1;
	mail->recipients[0] = sender;

	mail->subject = "Mail error";

	mail->body = "It seems that this mail does not exist";

	return mail;
}

//It pauses the program, you must
//press 'ENTER' for continue
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
			display("Error, enter a digit");
		}

		else if (digit < a || digit > b)
		{
			display("Error, enter a digit between " + std::to_string(a) + " and " + std::to_string(b));
			digit = -1;
		}

	} while (digit == -1);

	return digit;
}

//It centers a string on the middle of the pantalla,
//and surround it with what you want (space, guion...)
std::string GraphInter::center_word(std::string word, int length, std::string arround)
{
	if (word.size() != length)
	{
		for (int i = word.size(); i < length; i++)
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

//It prints the word you choose on console,
//after two empty spaces
void GraphInter::tab_word(std::string word)
{
	std::ostringstream tab;

	tab << std::setw(2 + word.size()) << word;

	display(tab.str());
}

//Returns a guion line
std::string GraphInter::linea()
{
	std::ostringstream line;

	line << std::setfill('-')
		<< std::setw(HORIZONTAL) << '-'
		<< std::setfill(' ');

	return line.str();
}

//Check the username to not have spaces, and
//not be longer than 15 characters
std::string GraphInter::valid_user()
{
	std::string id;
	bool id_right;

	display("Enter your id: ");

	do
	{
		id_right = true;

		enter(id);

		if (id.size() > 15)
		{
			display("Error, your id cannot be longer than 15 characters ");
			display("Enter your id: ");

			id_right = false;
		}
		else
		{
			for (int i = 0; i < int(id.size()) && id_right; i++)
			{
				if (id[i] == ' ')
				{
					display("Error, your id cannot contain a space");
					display("Enter your id: ");

					id_right = false;
				}
			}
		}		
	} while (!id_right);

	id = id + "@fdimail.com";

	return id;
}

//Draws a complete mail
void GraphInter::drawMail(const Mail* mail)
{
	std::cout << mail->to_string() << std::endl;
}

//Allow you to change your username
std::string GraphInter::changeUsername()
{
	std::string data = valid_user();

	checkUsername(data);

	return data;
}

//Allow you to change your password
std::string GraphInter::changePassword()
{
	std::string data;

	display("Enter your new password");

	enter(data);

	checkPassword(data);

	return data;
}

//Asks you to enter your username again, and
//checks both are the same.
void GraphInter::checkUsername(std::string& username)
{
	std::string newUsername;

	display("Confirm your new username: ");

	enter(newUsername);

	newUsername += "@fdimail.com";

	while (newUsername != username)
	{
		display("Error, usernames are not the same");
		display("Enter your new username:");

		enter(username);

		username += "@fdimail.com";

		display("Confirm your username:");

		enter(newUsername);

		newUsername += "@fdimail.com";
	}
}

//Asks you to enter your password again, and
//checks both are the same.
void GraphInter::checkPassword(std::string &password)
{
	std::string newPassword;

	display("Confirm your password: ");

	enter(newPassword);

	while (newPassword != password)
	{
		display("Error, passwords are not the same");
		display("Enter your new passwords:");

		enter(password);

		display("Confirm your passwords:");

		enter(newPassword);
	}
}

//Clears the console
void GraphInter::clearConsole(){ system("cls"); }

//Prints on the console the word you choose
void GraphInter::display(std::string error)
{
	std::cout << error << std::endl;
}

//Enters in console the word you choose
void GraphInter::enter(std::string &word)
{
	std::cin.sync();
	std::getline(std::cin, word);
	std::cin.clear();
}

//Enters in console the digit you choose
void GraphInter::enter(int &digit)
{
	std::cin.sync();
	std::cin >> digit;
	std::cin.clear();
}