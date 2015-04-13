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

	friend class Manager;
	friend class Session;

public:
	User(const std::string &idUser, const std::string &password);
	User();

	std::string getId() const { return id; }
	TrayList* active_tray() { return (active_list) ? &outbox : &inbox; }

	void save(std::ofstream &file)const;
	bool load(std::ifstream &file);

	bool checkPassword(const std::string &possible_password)const 
		{ return password == possible_password; }
	void changeTray() { active_list = !active_list; }
};
#endif