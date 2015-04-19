#include "Mail.h"
#include "Date.h"
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>

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
}

std::string Mail::to_string()const
{
	std::ostringstream flow;

	flow << this->from << std::setw(15) << showDate(this->date) << std::endl
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

