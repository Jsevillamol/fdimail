#ifndef USER
#define USER

#include <string>
#include <fstream>
#include "TrayList.h"

class User
{
private:
	std::string id, password;

	TrayList receivedMails;
	TrayList sentMails;

	bool active_list; //0 for received, 1 for sent
public:
	User(const std::string &idUser, const std::string &password);

	void save(std::ofstream &file)const;
	bool load(std::ifstream &file);

	bool checkPassword(const std::string &possible_password)const 
		{ return password == possible_password; }
	void changeTray() { active_list = !active_list; }
};
#endif