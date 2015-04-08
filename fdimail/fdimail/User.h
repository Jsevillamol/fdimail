#ifndef USER
#define USER

#include <string>
#include <fstream>
#include "TrayList.h"

class User
{
private:
	std::string name, password;

	TrayList receivedMails;
	TrayList sentMails;

	bool active_list; //0 for received, 1 for sent
public:
	User();
	~User();

	void initialize(const std::string &idUser, const std::string &password);
	void save(std::ofstream &file)const;
	bool load(std::ifstream &file);
	bool validPassword(const std::string &password)const;
	void changeTray();
};
#endif