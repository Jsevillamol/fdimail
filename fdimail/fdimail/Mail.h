#ifndef MAIL
#define MAIL

#include "GlobalConstants.h"
#include <fstream>
#include <string>
#include "Date.h"

/*----------------------------
This class contains the mail datos of a mail
and the neccesary functions to make it work
correctly
------------------------------*/

class Mail
{
public:
	std::string id;
	int user_count, //number of users with access to mail
		recipient_count;// number of user for a mail to be sent

	Date date;

	std::string recipients[MAX_RECIPIENTS];

	std::string from;

	std::string subject;
	std::string body;

	Mail(): user_count(0), recipient_count(1) {}

	const std::string& getId() const { return id; }
	int getCounter() const { return user_count; }
	int lowerCounter(){ return --user_count; }

	void save(std::ofstream &file)const;
	bool load(std::ifstream &file);

	const std::string to_string()const;
	const std::string header()const;

	std::string getsubject();
};
#endif