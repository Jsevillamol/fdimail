#include "GraphInter.h"
#include "Session.h"
#include "GlobalConstants.h"
#include "checkML.h"
#include "utilsWin.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <conio.h>

GraphInter* GraphInter::inter = nullptr;

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

int GraphInter::update(int key, int &elem, int max_elems)
{
	if (key == UP)
	{
		if (elem == 0)
		{
			return 0;
		}
		else return --elem;
	}
	else if (key == DOWN)
	{
		if (elem == max_elems - 1)
		{
			return max_elems - 1;
		}
		else return ++elem;
	}
	else return elem;
}

int GraphInter::menu(std::string elems[], int max_elems)
{
	int key = UP, elem = 0;

	do
	{
		display("Choose your desired option: ");

		for (int i = 0; i < max_elems; i++)
		{
			tab_word(elems[i], i, elem);
		}

		key = getKey(key);
		elem = update(key, elem, max_elems);

		clearConsole();

	} while (key != SPACE);

	return elem;
}

int GraphInter::trayMenu(Session* session, std::string elems[], int max_elems)
{
	int key = UP, elem = 0;

	do
	{
		showTray(session);

		display(linea());

		display("Choose your desired option: ");

		for (int i = 0; i < max_elems; i++)
		{
			tab_word(elems[i], i, elem);
		}

		key = getKey(key);
		elem = update(key, elem, max_elems);

		clearConsole();

	} while (key != SPACE);

	return elem;
}

//Options: sign in and sign up
int GraphInter::mainMenu()
{
	std::string elems[3];

	elems[0] = "Sign up";
	elems[1] = "Sign in";
	elems[2] = "Exit";

	return menu(elems, 3);
}

//Returns username and password
void GraphInter::logMenu(std::string &username, std::string &password)
{
	username = valid_user();

	display("Enter your password");

	password = HideLimitPassword();
}

//Shows active tray, returns user options (read mail, delete mail, etc)
int GraphInter::sessionMenu(Session* session)
{
	int key = UP, elem = 0;

	do
	{
		display("Mail of " + session->getUser()->getId());

		showTray(session);

		display("Choose your desired option: ");
		tab_word("Read mail", 0, elem);
		tab_word("Send mail", 1, elem);
		tab_word("Delete mail", 2, elem);

		if (session->get_active_list())
		{
			tab_word("See inbox", 3, elem);
		}
		else
		{
			tab_word("See outbox", 3, elem);
		}
		tab_word("Fast read of unread mails", 4, elem);
		tab_word("Account options", 5, elem);
		tab_word("Alias options", 6, elem);
		tab_word("Filter options", 7, elem);
		tab_word("Sign out", 8, elem);

		key = getKey(key);
		elem = update(key, elem, 9);

		clearConsole();

	} while (key != SPACE);

	return elem;
}

//Shows active tray, returns idMail of mail selected
Mail* GraphInter::selectMail(Session* session)
{
	int number;

	display("Enter the number of the mail you choose:");

	if (session->get_visible()->length() != 0)
	{
		number = digitBetween(1, session->get_visible()->length());

		return session->get_visible()->operator[](session->get_visible()->length() - number)->mail;
	}
	else
	{
		display("The active tray is empty");

		return nullptr;
	}
}

std::string GraphInter::selectAlias(Session* session)
{
	int number;

	display("Enter the number of the mail you choose:");

	number = digitBetween(1, session->getUser()->getContactlist()->length());

	return session->getUser()->getContactlist()->operator[](session->getUser()->getContactlist()->length() - number)->user;
}

//Shows mail, returns options answer, forward, or return to sessionMenu
int GraphInter::mailMenu()
{
	std::string elems[3];

	elems[0] = "Answer";
	elems[1] = "Forward";
	elems[2] = "Exit to session menu";

	return menu(elems, 3);
}

//Returns a full mail
Mail* GraphInter::newMail(const std::string &sender, ContactList* contactList)
{
	std::ostringstream ID;
	Mail* mail = new Mail;

	mail->from = sender;
	mail->date = time(0);
	mail->user_count = 2;

	ID << sender << "_" << mail->date;
	mail->id = ID.str();

	display("From: " + sender);

	display("How many recipients do you want this mail to be sent?");
	mail->recipient_count = digitBetween(0, MAX_RECIPIENTS);

	if (mail->recipient_count == 0)
	{
		delete mail;
		return nullptr;
	}
	else
	{
		send_to_multiple(mail, contactList);

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
Mail* GraphInter::forward(Mail* &originalMail, const std::string &sender, ContactList* contactList)
{
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

	if (mail->recipient_count == 0)
	{
		delete mail;
		return nullptr;
	}
	else
	{
		send_to_multiple(mail, contactList);

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

int GraphInter::FastName(ContactList* contactList)
{
	std::string elems[4];

	elems[0] = "Add an alias";
	elems[1] = "Delete an alias";
	elems[2] = "Delete all alias";
	elems[3] = "Exit to session menu";

	return menu(elems, 4);
}

void GraphInter::showFastNames(ContactList* contactList)
{
	if (contactList->length() != 0)
	{
		std::ostringstream alias;

		alias << "N" << std::setw(10) << "Username" << std::setw(30) << "Alias";

		display(alias.str());

		display(linea());

		for (int i = contactList->length() - 1; i >= 0; i--)
		{
			std::ostringstream newAlias;

			std::string user = std::to_string(contactList->length() - i) + ": " + contactList->operator[](i)->user;

			newAlias << std::setw(36) << std::left << user << std::left << contactList->operator[](i)->alias;

			display(newAlias.str());
		}
		display(linea());
	}
}

//Draws a complete mail
void GraphInter::drawMail(const Mail* mail)
{
	std::cout << mail->to_string() << std::endl;
	linea();
}

void GraphInter::showTray(Session* session)
{
	std::string title, thisMail;
	std::ostringstream menu;

	if (session->get_active_list())
	{
		title = center_word("Outbox", HORIZONTAL, "-");
	}
	else
	{
		title = center_word("Inbox", HORIZONTAL, "-");
	}

	display(linea());

	menu << title << "\n" << "\n" << "R N"
		<< std::setw(7) << "FROM" << std::setw(33)
		<< "SUBJECT" << std::setw(31) << "DATE";

	display(menu.str());

	display(linea());

	if (session->get_visible()->length() == 0)
	{
		display(center_word("You have no mails", HORIZONTAL, " "));
	}
	else
	{
		for (int i = session->get_visible()->length() - 1; i >= 0; i--)
		{
			std::ostringstream show;

			if (!session->get_visible()->operator[](i)->read)
			{
				show << "*";
			}
			else
			{
				show << " ";
			}

			Mail* mail = session->get_visible()->operator[](i)->mail;

			if (mail == nullptr)
			{
				mail = errorMail(session->getUser()->getId());
			}

			thisMail = mail->header();

			show << std::setw(2) << (session->get_visible()->length() - i) << " - " << thisMail;
			display(show.str());
		}
	}
	display(linea());
}

//Check the username to not have spaces, and
//not be longer than 15 characters
std::string GraphInter::valid_user()
{
	std::string id;
	bool id_right;

	do
	{
		id_right = true;

		clearConsole();

		display("Enter your id: ");
		enter(id);

		if (id.size() > 15)
		{
			display("Error, your id cannot be longer than 15 characters ");
			pause();

			id_right = false;
		}
		else if (id.size() == 0)
		{
			display("Error, your id cannot be empty ");
			pause();

			id_right = false;
		}
		else
		{
			std::ostringstream character;

			for (int i = 0; i < int(id.size()) && id_right; i++)
			{
				for (int j = 0; j < CENSORED_CHARS; j++)
				{
					if (id[i] == forbidden[j])
					{
						character << "(" << char(forbidden[j]) << ")";

						display("Error, your id cannot contain the character " + character.str());
						pause();

						id_right = false;
					}
					else if (id[i] <= 'Z' && 'A' <= id[i])
					{
						id[i] += 32; //transforms uppercase in lowercase
					}
				}
			}
		}
	} while (!id_right);

	id = id + "@fdimail.com";

	return id;
}

int GraphInter::choosefilter(Session* session)
{
	std::string elems[8];

	elems[0] = "Subject";
	elems[1] = "Date";
	elems[2] = "Emissor";
	elems[3] = "Recipients";
	elems[4] = "Body";
	elems[5] = "Read";
	elems[6] = "Unread";
	elems[7] = "Exit to session menu";

	return menu(elems, 8);
}

int GraphInter::chooseorder(Session* session)
{
	std::string elems[2];

	elems[0] = "Subject";
	elems[1] = "Date";

	return menu(elems, 2);
}

int GraphInter::filter()
{
	std::string elems[4];

	elems[0] = "Change order";
	elems[1] = "Change filter";
	elems[2] = "Quit filter";
	elems[3] = "Exit to session menu";

	return menu(elems, 4);
}

//It pauses the program, you must
//press 'ENTER' for continue
void GraphInter::pause()
{
	std::cin.sync();
	std::cin.get();
}

//Clears the console
void GraphInter::clearConsole(){ system("cls"); }

//Little options menu
int GraphInter::WhatToDelete(Session* session)
{
	std::string elems[3];

	elems[0] = "Choose mail";
	elems[1] = "Delete all mails";
	elems[2] = "Exit to session menu";

	return trayMenu(session, elems, 3);
}

int GraphInter::Invert()
{
	std::string elems[2];

	elems[0] = "Order list";
	elems[1] = "Invert list";

	return menu(elems, 2);
}

//Little options menu
int GraphInter::AccountOptions()
{
	std::string elems[4];

	elems[0] = "Change username";
	elems[1] = "Change password";
	elems[2] = "Delete account";
	elems[3] = "Exit to session menu";

	return menu(elems, 4);
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

	newPassword = HidePassword();

	while (newPassword != password)
	{
		display("Error, passwords are not the same");
		display("Enter your new passwords:");

		password = HideLimitPassword();

		display("Confirm your passwords:");

		newPassword = HidePassword();

		display("");
	}
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

void GraphInter::enter(char* str)
{
	std::cin.sync();
	std::cin >> str;
	std::cin.clear();
}

std::string GraphInter::HideLimitPassword()
{
	std::string word;
	do
	{
		word = HidePassword();

		if (word.size() < PASSWORD_MIN_LENGTH)
		{
			display("");
			std::string msg = std::string("Error, your password must contain ") + std::to_string(PASSWORD_MIN_LENGTH) + std::string(" characters or more");
			display(msg);
			display("Enter your password");
		}
	} while (word.size() < PASSWORD_MIN_LENGTH);

	display("");

	return word;
}

std::string GraphInter::HidePassword()
{
	std::cout.flush();
	int i;
	char word[50];

	//Enter new password
	i = 0;
	word[i] = (unsigned char)_getch();
	std::cout.flush();

	while (word[i] != 13) // si no presiona ENTER
	{
		if (word[i] != 8)  // no es retroceso
		{
			display('*'); // muestra por pantalla
			i++;
		}
		else if (i > 0)    // es retroceso y hay caracteres
		{
			std::cout << (char)8 << (char)32 << (char)8;
			i --;  //el caracter a borrar e el backspace
		}

		word[i] = (unsigned char)_getch();
		std::cout.flush();
	}

	word[i] = NULL;

	//display("");

	return word;
}

//Prints on the console the word you choose
void GraphInter::display(std::string error)
{
	std::cout << error << std::endl;
}

void GraphInter::display(char sign)
{
	std::cout << sign;
}

void GraphInter::send_to_multiple(Mail* mail, ContactList* contactList)
{
	int i;
	for (i = 0; i < mail->recipient_count; i++)
	{
		if (i == 0)
		{
			display("To: ");
		}
		else
		{
			display("CC: ");
		}

		std::string recipient;

		//std::cin.ignore();
		enter(recipient);

		mail->recipients[i] = contactList->SearchFastName(recipient);

		if (mail->recipients[i] == "@fdimail.com")
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
	
		mail->user_count = mail->recipient_count + 1;
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
	word = word;

	return word;
}

//It prints the word you choose on console,
//after two empty spaces
void GraphInter::tab_word(std::string word, int pos, int cont)
{
	std::ostringstream tab;

	if (pos == cont)
	{
		word = "* " + word;
	}
	else
	{
		word = "  " + word;
	}
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