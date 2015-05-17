#include "Manager.h"
#include "GraphInter.h"
#include <sstream>

Manager* Manager::manager = nullptr;

Manager::Manager(const std::string &new_domain) :
domain(new_domain)
{
	if (manager == nullptr){
		manager = this;
		bootUp();
	}
	else GraphInter::get()->display("Manager cannot be instantiated twice!");
}

Manager::~Manager()
{
	shutDown();
}

//Loads the users and mails from the default files
//If the load cannot de made, it asks you to enter
//the savefile location
void Manager::bootUp()
{
	std::ostringstream mail_file, user_file;
	mail_file << domain << "_mails.txt";
	user_file << domain << "_users.txt";

	manualMails(mail_file.str());
	manualUsers(user_file.str());
}

//It saves the users and mails on the default files
void Manager::shutDown()
{
	std::ostringstream mail_file, user_file;
	mail_file << domain << "_mails.txt";
	user_file << domain << "_users.txt";

	userList.save(user_file.str());
	mailList.save(mail_file.str());
}

//Allows a user to enter in his account, if is already exist
User* Manager::registerUser()
{
	std::string idUser;
	std::string last_password;
	GraphInter::get()->logMenu(idUser, last_password);
	User* user = (userList.get(idUser));
	if  (user != nullptr)
	{
		if (user->checkPassword(last_password))
			return user;
		else
		{
			GraphInter::get()->display("Wrong password");
			GraphInter::get()->pause();
			return nullptr;
		}
	}
	else
	{
		GraphInter::get()->display("User does not exist");
		GraphInter::get()->pause();
		return nullptr;
	}
}

//It allows a new user to create an account
User* Manager::createAccount()
{
	std::string idUser;
	std::string last_password;
	GraphInter::get()->logMenu(idUser, last_password);
	
	if (userList.get(idUser) == nullptr)
	{
		GraphInter::get()->checkPassword(last_password);
		User* user = new User(idUser, last_password);
		userList.insert(user);
		return user;
	}
	else
	{
		GraphInter::get()->display("This username already exists");
		GraphInter::get()->pause();
		return nullptr;
	}
}

//Allows a user to delete his account
void Manager::deleteAccount(User* user)
{
	//Delete inbox
	while (user->getInbox()->length() > 0)
	{
		deleteMail(user->getInbox(), user->getInbox()->operator[](0)->getId());
	}
	//Delete outbox
	while (user->getOutbox()->length() > 0)
	{
		deleteMail(user->getOutbox(), user->getOutbox()->operator[](0)->getId());
	}

	userList.destroy(user->getId());
}

//it search the mail recipients, and if it find them
//send the mail you choose to the recpiets it finds
void Manager::sendMail(User* user, Mail* mail)
{
	//Add to database
	if (mailList.insert(mail))
	{
		//Add to sender's outbox
		tElemTray* elem = new tElemTray(mail);
		elem->read = true;

		user->getOutbox()->insert(elem);

		for (int j = 0; j < mail->recipient_count; j++)
		{
			if (userList.get(mail->recipients[j]) != nullptr)
			{
				//Add to receiver's inbox
				userList.get(mail->recipients[j])->getInbox()->insert(new tElemTray(mail));
			}
			else
			{
				GraphInter::get()->display("Destinatary " + mail->recipients[j] + " not found");
				GraphInter::get()->display("He was not sent the mail");
				GraphInter::get()->pause();
			}
		}
	}
	else
	{
		GraphInter::get()->display("MailList full");
		GraphInter::get()->pause();
	}
}

//Send an answer mail
bool Manager::answer(User* user, Mail* mail)
{
	if (userList.get(mail->recipients[0]) != nullptr)
	{
		//Add to database
		mailList.insert(mail);

		//Add to sender's outbox
		user->getOutbox()->insert(new tElemTray(mail));
		user->getOutbox()->get(mail->getId())->read = true;

		//Add to receiver's inbox
		//std::cout << "Destinatary dir: " << userList.get(mail->to) << std::endl;
		userList.get(mail->recipients[0])->getInbox()->insert(new tElemTray(mail));

		return true;
	}
	else return false;
}

//Delete the mail you choose from the tray where you are
void Manager::deleteMail(TrayList* box, const std::string &idMail)
{
	Mail* mail = mailList.get(idMail);

	//Delete from user's in/outbox
	box->destroy(idMail);

	//Delete from database
	mailList.delete_mail(idMail);
}

//Asks you for the userfile location, just if
//is not found in the default url
void Manager::manualUsers(std::string &name)
{
	std::string userLocation = "Hola"; //to avoid the string to be empty

	while (userLocation != "" && !userList.load(name))
	{
		GraphInter::get()->display("Could not load userList");
		GraphInter::get()->display("Enter the file url ((ENTER) for continue)");
		GraphInter::get()->enter(userLocation);

		if (userLocation != "")
		{
			name = userLocation;
		}
	}
}

//Asks you for the mailfile location, just if
//is not found in the default url
void Manager::manualMails(std::string &name)
{
	std::string mailLocation = "Hola"; //to avoid the string to be empty

	while (mailLocation != "" && !mailList.load(name))
	{
		GraphInter::get()->display("Could not load mailList");
		GraphInter::get()->display("Enter the file url ((ENTER) for continue)");
		GraphInter::get()->enter(mailLocation);

		if (mailLocation != "")
		{
			name = mailLocation;
		}
	}
}
