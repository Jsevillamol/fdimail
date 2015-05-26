#include "Mail.h"
#include "Date.h"
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>

//It saves a mail in the file you choose
void Mail::save(std::ofstream &file) const
{
	file << this->id << std::endl << this->user_count << std::endl << this->date
		<< std::endl << this->from << std::endl << this->recipient_count << std::endl;

	for (int i = 0; i < this->recipient_count; i++)
	{
		file << this->recipients[i] << std::endl;
	}
	file << this->subject << std::endl 
		<< this->body << "#" << std::endl;
}

//It loads a mail from the file you choose
bool Mail::load(std::ifstream &file)
{
	file >> this->id;

	if (id != "XXX" && !file.fail())
	{
		file >> this->user_count;

		if (!file.fail())
		{
			file >> this->date;

			if (!file.fail())
			{
				file >> this->from;

				if (!file.fail())
				{
					file >> this->recipient_count;

					if (!file.fail())
					{
						for (int i = this->recipient_count - 1; i >= 0; i--)
						{
							file >> this->recipients[i];
						}

						if (!file.fail())
						{
							file.ignore();
							std::getline(file, this->subject);

							if (!file.fail())
							{
								std::getline(file, this->body, '#');

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
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

//It transform a mail to a string form 
//so that you can work with all the mail
//at once
const std::string Mail::to_string() const
{
	std::ostringstream flow;

	flow << "From: " << this->from << std::setw(55) << showDate(this->date) << std::endl;

	for (int i = 0; i < this->recipient_count; i++)
	{
		flow << "To: " << this->recipients[i] << std::endl;
	}
	flow << std::endl << "Subject: " << this->subject << std::endl
		<< std::endl << this->body;

	return flow.str();
}

//Takes the mail sender, its subject, and its date (just the day)
//and transform it into a string
const std::string Mail::header()const
{
	std::ostringstream lowFlow;

	lowFlow << std::setw(30) << std::left << this->from << std::setw(34) << std::left << this->subject << showDay(this->date);

	return lowFlow.str();
}

std::string Mail::getsubject()
{
	std::string subject = this->subject;
	while (subject.substr(0, 4) == "Re: ")
	{
		subject = subject.substr(4);
	}

	return subject;
}