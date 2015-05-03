#ifndef MAIL
#define MAIL

#include <string>
#include <fstream>
#include "Date.h"
#include "GlobalConstants.h"

class Mail
{
public:
	std::string id;
	int user_count, recipient_count; //number of users with access to mail
	Date date;

	std::string recipients[MAX_RECIPIENTS];

	std::string from;

	std::string subject;
	std::string body;

	Mail(): user_count(0), recipient_count(1) {}

	const std::string& getId() const { return id; }
	int getCounter() const { return user_count; }

	void save(std::ofstream &file)const;
	bool load(std::ifstream &file);

	int lowerCounter(){ return --user_count; }
	const std::string to_string()const;
	const std::string header()const;
};
#endif