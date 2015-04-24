#include "Manager.h"
#include <sstream>

Manager::Manager(const std::string &new_domain) :
	domain(new_domain)
{
	if (!bootUp()) GraphInter::get()->error("Could not boot");
}

Manager::~Manager()
{
	shutDown();
}

bool Manager::bootUp()
{
	std::ostringstream mail_file, user_file;
	mail_file << domain << "_mails.txt";
	user_file << domain << "_users.txt";
	if (!mailList.load(mail_file.str())) GraphInter::get()->error("Could not load maillist");
	if (!userList.load(user_file.str())) GraphInter::get()->error("Could not load userlist");
	return true;
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
			std::cout << "Wrong password"<< std::endl;
			return nullptr;
		}
	}
	else
	{
		std::cout << "User does not exist" << std::endl;
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

		return nullptr;
	}
}

void Manager::sendMail(User* user, Mail* mail)
{
	if (userList.get(mail->getReceiver()) != nullptr)
	{
		//Add to database
		mailList.insert(mail);

		//Add to sender's outbox
		user->getOutbox()->insert(new tElemTray(mail->getId()));
		user->getOutbox()->get(mail->getId())->read = true;

		//Add to receiver's inbox
		//std::cout << "Destinatary dir: " << userList.get(mail->to) << std::endl;
		userList.get(mail->getReceiver())->getInbox()->insert(new tElemTray(mail->getId()));
	}
	else std::cout << "Destinatary not found in the user database" << std::endl;
}

void Manager::deleteMail(User* user, const std::string &idMail)
{
	//Delete from database
	mailList.delete_mail(idMail);

	//Delete from user's in/outbox
	user->active_tray()->destroy(idMail);
}