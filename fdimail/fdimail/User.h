#ifndef USER
#define USER

#include <string>
#include <fstream>
#include "TrayList.h"

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
	TrayList* getInbox() { return &inbox; }
	TrayList* getOutbox() { return &outbox; }
	TrayList* active_tray() { return active_list ? &outbox : &inbox; }
	bool* getTray(){ return &active_list; }

	void save(std::ofstream &file)const;
	bool load(std::ifstream &file);

	bool checkPassword(const std::string &possible_password)const 
		{ return password == possible_password; }
	
};
#endif