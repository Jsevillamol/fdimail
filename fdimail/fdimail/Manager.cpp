#include "Manager.h"
#include <sstream>
#include <iostream>

Manager::Manager(const std::string &new_domain) :
	domain(new_domain)
{
	if (!bootUp()) throw "Could not boot";
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
	if(mailList.load(mail_file.str()) && userList.load(user_file.str())) return true;
	else return false;
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
	std::string idUser, password;
	std::cin >> idUser;
	User* user;
	if (user = userList.get(idUser))
	{
		std::cin >> password;
		if (user->checkPassword(password))
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
	std::string idUser, password;
	std::cin >> idUser;
	if (!userList.get(idUser))
	{
		std::cin >> password;
		User* user = new User(idUser, password);
		userList.insert(user);
		return user;
	}
	else return nullptr;
}

void Manager::sendMail(User &user, Mail* mail)
{
	//Add to database
	mailList.insert(mail);

	//Add to sender's outbox
	user.outbox.insert(new tElemTray(mail->getId()));

	//Add to receiver's inbox
	userList.get(mail->getReceiver())->inbox.insert(new tElemTray(mail->getId));

}

void Manager::deleteMail(User &user, const std::string &idMail)
{
	//Delete from database
	mailList.delete_mail(idMail);

	//Delete from user's in/outbox
	((user.active_list) ? user.outbox : user.inbox).destroy(idMail);
}