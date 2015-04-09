#include "Mail.h"

Mail Mail::newMail(const std::string &issuing)
{
	return (*this);
}

Mail Mail::answerMail(const Mail &originalMail, const std::string &issuing)
{
	return(*this);
}

void Mail::save(std::ofstream &file) const
{

}

bool Mail::load(std::ifstream &file)
{
	return true;//Placeholder
}

std::string Mail::to_string()const
{
	return ""; //Placeholder
}

std::string Mail::header()const
{
	return ""; //Placeholder
}

