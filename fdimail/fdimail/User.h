#ifndef USER
#define USER

#include <string>
#include <fstream>

class User
{
private:
	std::string name, password;
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