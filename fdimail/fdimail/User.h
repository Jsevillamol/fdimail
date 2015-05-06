#ifndef USER
#define USER

#include <string>
#include <fstream>
#include "TrayList.h"
#include "Encript.h"

class User
{
private:
	std::string id, password;

	TrayList inbox;
	TrayList outbox;

	bool active_list; //0 for inbox, 1 for outbox

public:
	User(const std::string idUser, const std::string password);
	User();

	const std::string& getId() const { return id; }
	std::string& setId(std::string newId) { return id = newId ; }
	std::string& setPassword(std::string newPassword){ return password = sha1(newPassword); }
	TrayList* getInbox() { return &inbox; }
	TrayList* getOutbox() { return &outbox; }
	TrayList* active_tray() { return active_list ? &outbox : &inbox; }
	bool* getTray(){ return &active_list; }

	void save(std::ofstream &file)const;
	bool load(std::ifstream &file);

	bool checkPassword(const std::string &possible_password)const 
		{ return password == sha1(possible_password); }
	
};
#endif