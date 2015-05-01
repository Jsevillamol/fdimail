#ifndef MAIL
#define MAIL

#include <string>
#include <fstream>
#include "Date.h"

class Mail
{
public:
	std::string id;
	int user_count; //number of users with access to mail
	Date date;

	std::string from;
	std::string to;

	std::string subject;
	std::string body;

	Mail(): user_count(0) {}

	const std::string& getId() const { return id; }
	int getCounter() const { return user_count; }
	std::string getReciver() const { return to; }
	const std::string& getReceiver() const { return to; }

	void save(std::ofstream &file)const;
	bool load(std::ifstream &file);

	int lowerCounter(){ return --user_count; }
	const std::string to_string()const;
	const std::string header()const;
};
#endif