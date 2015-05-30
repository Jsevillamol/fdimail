#ifndef USER
#define USER

#include "ContactList.h"
#include "TrayList.h"
#include "Encript.h"
#include <fstream>
#include <string>

/*----------------------------
Contains the user variables, and the
functions necessary for working with it
------------------------------*/

class User
{
public:
	User(const std::string idUser, const std::string password);
	User();

	const std::string& getId() const { return id; }

	std::string& setId(std::string newId) { return id = newId ; }
	std::string& setPassword(std::string newPassword){ return password = sha1(newPassword); }

	TrayList* getInbox() { return &inbox; }
	TrayList* getOutbox() { return &outbox; }
	ContactList* getContactlist() { return &contactList; }

	void save(std::ofstream &file)const;
	bool load(std::ifstream &file);

	bool checkPassword(const std::string &possible_password)const 
		{ return password == sha1(possible_password); }

private:
	std::string id, password;

	ContactList contactList;
	TrayList inbox;
	TrayList outbox;
	
};
#endif