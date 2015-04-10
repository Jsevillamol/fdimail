#ifndef MAIL
#define MAIL


#include <string>
#include <fstream>
#include "Date.h"

class Mail
{
private:
	std::string id;
	int user_count; //number of users with access to mail
	Date date;

	std::string from;
	std::string to;

	std::string subject;
	std::string body;

public:

	std::string getid(){ return id; }

	Mail newMail(const std::string &issuing);
	Mail answerMail(const Mail &originalMail);

	void save(std::ofstream &file)const;
	bool load(std::ifstream &file);

	int lowerCounter(){ return --user_count; }
	std::string to_string()const;
	std::string header()const;
};
#endif