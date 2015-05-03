#include "Manager.h"
#include <sstream>

Manager::Manager(const std::string &new_domain) :
	domain(new_domain)
{
	bootUp();
}

Manager::~Manager()
{
	shutDown();
}

void Manager::bootUp()
{
	std::ostringstream mail_file, user_file;
	mail_file << domain << "_mails.txt";
	user_file << domain << "_users.txt";

	manualyMails(mail_file.str());
	manualyUsers(user_file.str());
}

void Manager::shutDown()
{
	std::ostringstream mail_file, user_file;
	mail_file << domain << "_mails.txt";
	user_file << domain << "_users.txt";

	mailList.save(mail_file.str());
	userList.save(user_file.str());
}

User* Manager::registerUser()
{
	std::string idUser, password, last_password;
	GraphInter::get()->logMenu(idUser, last_password);
	User* user = (userList.get(idUser));
	if  (user != nullptr)
	{
		if (user->checkPassword(last_password))
			return user;
		else
		{
			GraphInter::get()->error("Wrong password");
			GraphInter::get()->pause();
			return nullptr;
		}
	}
	else
	{
		GraphInter::get()->error("User does not exist");
		GraphInter::get()->pause();
		return nullptr;
	}
}

User* Manager::createAccount()
{
	std::string idUser, last_password;
	GraphInter::get()->logMenu(idUser, last_password);
	
	if (!userList.get(idUser))
	{
		GraphInter::get()->check_password(last_password);
		User* user = new User(idUser, last_password);
		userList.insert(user);
		return user;
	}
	else
	{
		GraphInter::get()->error("This username already exists");
		GraphInter::get()->pause();
		return nullptr;
	}
}

void Manager::sendMail(User* user, Mail* mail)
{
	//Add to database
	mailList.insert(mail);

	//Add to sender's outbox
	user->getOutbox()->insert(new tElemTray(mail->getId()));
	user->getOutbox()->get(mail->getId())->read = true;

	for (int j = 0; j < mail->recipient_count; j++)
	{
		if (userList.get(mail->recipients[j]) != nullptr)
		{
			//Add to receiver's inbox
			//std::cout << "Destinatary dir: " << userList.get(mail->to) << std::endl;
			userList.get(mail->recipients[j])->getInbox()->insert(new tElemTray(mail->getId()));
		}
		else
		{
			GraphInter::get()->error("Destinatary " + mail->recipients[j] + " not found");
			GraphInter::get()->error("The mail was not sent to him");
		}
	}
}

bool Manager::answer(User* user, Mail* mail)
{
	if (userList.get(mail->recipients[0]) != nullptr)
	{
		//Add to database
		mailList.insert(mail);

		//Add to sender's outbox
		user->getOutbox()->insert(new tElemTray(mail->getId()));
		user->getOutbox()->get(mail->getId())->read = true;

		//Add to receiver's inbox
		//std::cout << "Destinatary dir: " << userList.get(mail->to) << std::endl;
		userList.get(mail->recipients[0])->getInbox()->insert(new tElemTray(mail->getId()));

		return true;
	}
	else return false;
}

void Manager::deleteMail(TrayList* box, const std::string &idMail)
{
	//Delete from database
	mailList.delete_mail(idMail);

	//Delete from user's in/outbox
	box->destroy(idMail);
}

void Manager::manualyUsers(std::string &name)
{
	std::string userLocation = "Hola"; //to avoid the string to be empty

	while (userLocation != "" && !userList.load(name))
	{
		GraphInter::get()->error("Could not load userList");
		GraphInter::get()->error("Enter the file url ((ENTER) for continue)");
		GraphInter::get()->enter(userLocation);

		if (userLocation != "")
		{
			name = userLocation;
		}
	}
}

void Manager::manualyMails(std::string &name)
{
	std::string mailLocation = "Hola"; //to avoid the string to be empty

	while (mailLocation != "" && !mailList.load(name))
	{
		GraphInter::get()->error("Could not load mailList");
		GraphInter::get()->error("Enter the file url ((ENTER) for continue)");
		GraphInter::get()->enter(mailLocation);

		if (mailLocation != "")
		{
			name = mailLocation;
		}
	}
}
