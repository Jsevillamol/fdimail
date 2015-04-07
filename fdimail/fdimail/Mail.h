#ifndef MAIL
#define MAIL

#include <string>
#include <fstream>

class Mail
{
public:
	Mail();
	~Mail();

	void newMail(const std::string &issuing);
	void answerMal(Mail &mail, const std::string issuing)const;
	void save(std::ofstream file)const;
	bool load(std::ifstream file);
	std::string to_string()const;
	std::string header()const;
};
#endif