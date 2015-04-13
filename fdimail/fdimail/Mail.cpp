#include "Mail.h"
#include "Date.h"
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>

Mail* Mail::newMail(const std::string &issuing)
{
	std::ostringstream ID;

	this->from = issuing;
	this->date = time(0);

	ID << issuing << "_" << this->date;
	this->id = ID.str();

	std::cout << "From: " << issuing << std::endl;

	std::cout << "To: ";
	std::cin >> this->to;

	std::cout << "Subject: ";
	std::cin >> this->subject;

	std::cout << "Body: ";
	std::cin >> this->body;

	return this;
}

Mail* Mail::answerMail(const Mail* originalMail)
{
	std::ostringstream ID, BODY, SUBJECT;
	std::string WhatToSay;

	SUBJECT << "Re: " << originalMail->subject;

	this->from = originalMail->to;
	this->date = time(0);
	this->to = originalMail->from;
	this->subject = SUBJECT.str();


	ID << originalMail->to << "_" << this->date;
	this->id = ID.str();



	std::cout << "From: " << originalMail->to << std::endl;

	std::cout << "To: ";
	this->to = originalMail->from;

	std::cout << "Subject: ";
	std::cin >> this->subject;

	std::cout << "Body: ";
	std::cin >> WhatToSay;

	BODY << WhatToSay << std::endl << std::endl
		<< originalMail->to_string();//ultimo mail;

	this->body = BODY.str();

	return this;
}

void Mail::save(std::ofstream &file) const
{
	file << this->from << std::endl << this->date << std::endl
		<< this->to << std::endl << this->subject << std::endl 
		<< this->body << std::endl << "X" << std::endl;
}

bool Mail::load(std::ifstream &file)
{
	file >> this->from;

	if (!file.fail())
	{
		file >> this->date;

		if (!file.fail())
		{
			file >> this->to;

			if (!file.fail())
			{
				file >> this->subject;

				if (!file.fail())
				{
					file >> this->body;

					if (!file.fail()) return true;
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
	return true;//Placeholder
}

std::string Mail::to_string()const
{
	std::ostringstream flow;

	flow << this->from << std::setw(15) << this->date << std::endl
		<< this->to << std::endl << this->subject << std::endl
		<< std::endl << this->body;

	return flow.str();
}

std::string Mail::header()const
{
	std::ostringstream lowFlow;

	lowFlow << this->from << std::setw(29) << this->to << std::setw(29) << showDay(this->date);

	return lowFlow.str();
}

