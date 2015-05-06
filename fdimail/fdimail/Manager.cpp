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

	mailList.save(mail_file.str());
	userList.save(user_file.str());
}

//Allows a user to enter in his account, if is already exist
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
	std::string idUser, last_password;
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
void Manager::deleteAccount(const std::string &id)
{
	User* user = userList.get(id);
	int inlenth = user->getInbox()->length();
	int outlenth = user->getOutbox()->length();

	//Delete inbox
	for (int i = 0; i < inlenth; i++)
	{
		mailList.delete_mail(user->getInbox()->operator[](i)->getId());
	}
	//Delete outbox
	for (int i = 0; i < outlenth; i++)
	{
		mailList.delete_mail(user->getOutbox()->operator[](i)->getId());
	}
	userList.destroy(id);
}

//Allows a user to change his username
void Manager::ChangeUsername(User* user)
{
	std::string newUsername = GraphInter::get()->changeUsername();

	user->setId(newUsername);
}

//Allows a user to change his password
void Manager::ChangePassword(User* user)
{
	std::string newPassword = GraphInter::get()->changePassword();

	user->setPassword(newPassword);
}

void Manager::AddFastName(User* user)
{
	if (user->fullNames())
	{
		GraphInter::get()->display("You cannot asign more alias");
		GraphInter::get()->pause();
	}
	else
	{
		int i, j;
		std::string idUser, newId;
		bool name_right;

		GraphInter::get()->display("Enter the user id you want:");
		GraphInter::get()->enter(idUser);

		if (userList.get(idUser) == nullptr)
		{
			GraphInter::get()->display("This user does not exist");
			GraphInter::get()->pause();
		}
		else
		{
			for (i = 0; i < user->getName() && user->getNumName(i).user != idUser; i++) {}

			if (i != user->getName())
			{
				GraphInter::get()->display("This username already has an alias");
				GraphInter::get()->pause();
			}
			else
			{
				GraphInter::get()->display("Enter the alias you choose for this user (cannot contain '@'):");

				do
				{
					name_right = true;

					GraphInter::get()->enter(newId);

					if (newId.size() == 0)
					{
						GraphInter::get()->display("Error, the alias cannot be empty");
						name_right = false;
					}
					else
					{
						for (int k = 0; k < newId.size() && name_right; k++)
						{
							if (newId[i] == '@')
							{
								GraphInter::get()->display("Error, the alias cannot contain '@'");
								name_right = false;
							}
							else if (newId[i] == ' ')
							{
								GraphInter::get()->display("Error, the alias cannot contain a space");
								name_right = false;
							}
						}
					}
				} while (!name_right);

				for (j = 0; j < user->getName() && user->getNumName(j).alias != newId; j++) {}

				if (j != user->getName())
				{
					GraphInter::get()->display("This alias is already asigned to an user");
					GraphInter::get()->pause();
				}
				else
				{
					user->getNumName(user->upNameCount()) = tContact(idUser, newId);
				}
			}
		}
	}
}

//it search the mail recipients, and if it find them
//send the mail you choose to the recpiets it finds
void Manager::sendMail(User* user, Mail* mail)
{
	//Add to database
	if (mailList.insert(mail))
	{
		//Add to sender's outbox
		user->getOutbox()->insert(new tElemTray(mail->getId()));

		user->getOutbox()->get(mail->getId())->read = true;

		for (int j = 0; j < mail->recipient_count; j++)
		{
			if (userList.get(mail->recipients[j]) != nullptr)
			{
				//Add to receiver's inbox
				userList.get(mail->recipients[j])->getInbox()->insert(new tElemTray(mail->getId()));
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
		user->getOutbox()->insert(new tElemTray(mail->getId()));
		user->getOutbox()->get(mail->getId())->read = true;

		//Add to receiver's inbox
		//std::cout << "Destinatary dir: " << userList.get(mail->to) << std::endl;
		userList.get(mail->recipients[0])->getInbox()->insert(new tElemTray(mail->getId()));

		return true;
	}
	else return false;
}

//Delete the mail you choose from the thay where you are
void Manager::deleteMail(TrayList* box, const std::string &idMail)
{
	Mail* mail = mailList.get(idMail);

	//Delete from user's in/outbox
	box->destroy(idMail);

	mail->user_count--;

	if (mail->user_count == 0)
	{
		//Delete from database
		mailList.delete_mail(idMail);
	}
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
