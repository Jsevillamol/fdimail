#include "Mail.h"
#include "Date.h"
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>

void Mail::save(std::ofstream &file) const
{
	file << this->id << std::endl << this->user_count << std::endl << this->date << std::endl << this->from << std::endl;

	for (int i = 0; i < this->recipient_count; i++)
	{
		file << this->recipients[i] << std::endl;
	}
	file << std::endl << this->subject << std::endl 
		<< this->body << "#" << std::endl;
}

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
					for (int i = 0; i < this->user_count - 2; i++)
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

const std::string Mail::to_string() const
{
	std::ostringstream flow;

	flow << "From: " << this->from << std::setw(55) << showDate(this->date) << std::endl;

	for (int i = 0; i < this->recipient_count; i++)
	{
		flow << "To: " << this->recipients[i];
	}
	flow << std::endl << "Subject: " << this->subject << std::endl
		<< std::endl << this->body;

	return flow.str();
}

const std::string Mail::header()const
{
	std::ostringstream lowFlow;

	lowFlow << std::setw(30) << std::left << this->from << std::setw(34) << std::left << this->subject << showDay(this->date);

	return lowFlow.str();
}