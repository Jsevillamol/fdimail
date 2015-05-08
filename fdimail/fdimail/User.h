#ifndef USER
#define USER

#include <string>
#include <fstream>
#include "TrayList.h"
#include "ContactList.h"
#include "Encript.h"

/*
Contains the user variables, and the
functions necessary for working with it
*/

class User
{
private:
	std::string id, password;

	ContactList contactList;
	TrayList inbox;
	TrayList outbox;


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
	
};
#endif