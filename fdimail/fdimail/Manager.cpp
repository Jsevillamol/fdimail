#include "Manager.h"
#include "Session.h"
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
void Manager::deleteAccount(const std::string &id)
{
	User* user = userList.get(id);
	int inlenth = user->getInbox()->length();
	int outlenth = user->getOutbox()->length();
	int namelenth = user->getContactlist()->length();

	//Delete inbox
	for (int i = 0; i < namelenth; i++)
	{
		user->getContactlist()->destroy(user->getContactlist()->operator[](i)->getId());
	}
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
	if (user->getContactlist()->full())
	{
		GraphInter::get()->display("You cannot asign more alias");
		GraphInter::get()->pause();
	}
	else
	{
		int i, j;
		std::string idUser, newId;
		bool name_right;

		GraphInter::get()->display("Enter the user id you want to asign:");
		GraphInter::get()->enter(idUser);

		if (userList.get(idUser) == nullptr || userList.get(idUser + "@fdimail.com") == nullptr)
		{
			GraphInter::get()->display("This user does not exist");
			GraphInter::get()->pause();
		}
		else if (idUser == user->getId())
		{
			GraphInter::get()->display("There is already an asigned alias for your own username");
			GraphInter::get()->pause();
		}
		else
		{
			for (i = 0; i < user->getContactlist()->length() && user->getContactlist()->operator[](i)->getId() != idUser; i++) {}

			if (i != user->getContactlist()->length())
			{
				GraphInter::get()->display("This username already has an alias");
				GraphInter::get()->pause();
			}
			else
			{
				do
				{
					name_right = true;

					GraphInter::get()->clearConsole();
					GraphInter::get()->display("User: " + idUser);
					GraphInter::get()->display("Enter the alias you choose for this user (cannot contain '@'):");
					GraphInter::get()->enter(newId);

					if (newId.size() == 0)
					{
						GraphInter::get()->display("Error, the alias cannot be empty");
						GraphInter::get()->pause();

						name_right = false;
					}
					else if (newId == "Me")
					{
						GraphInter::get()->display("Error, this is a default alias, you cannot asign it");
						GraphInter::get()->pause();

						name_right = false;
					}
					else
					{
						for (int k = 0; k < newId.size() && name_right; k++)
						{
							if (newId[i] == '@')
							{
								GraphInter::get()->display("Error, the alias cannot contain '@'");
								GraphInter::get()->pause();

								name_right = false;
							}
							else if (newId[i] == ' ')
							{
								GraphInter::get()->display("Error, the alias cannot contain a space");
								GraphInter::get()->pause();

								name_right = false;
							}
						}

						for (j = 0; j < user->getContactlist()->length() && user->getContactlist()->operator[](i)->getAlias() != newId; j++) {}

						if (j != user->getContactlist()->length())
						{
							GraphInter::get()->display("This alias is already asigned to an user");
							GraphInter::get()->pause();

							name_right = false;
						}
					}
				} while (!name_right);

				tContact* newContact = new tContact(idUser, newId);

				user->getContactlist()->insert(newContact);
			}
		}
	}
}

void Manager::AliasOptions(Session* session)
{
	int option = GraphInter::get()->FastName();

	if (option == 1)
	{
		AddFastName(session->getUser());
	}
	else
	{
		if (session->getUser()->getContactlist()->length() == 0)
		{
			GraphInter::get()->display("You have no alias to delete");
			GraphInter::get()->pause();
		}
		else
		{
			if (option == 2)
			{
				std::string name = GraphInter::get()->selectMail(session);

				deleteName(session->getUser(), name);
			}
			else if (option == 3)
			{
				int namelenth = session->getUser()->getContactlist()->length();

				for (int i = 0; i < namelenth; i++)
				{
					session->getUser()->getContactlist()->destroy(session->getUser()->getContactlist()->operator[](i)->getId());
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

void Manager::deleteName(User* user, const std::string &idName)
{
	user->getContactlist()->destroy(idName);
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
