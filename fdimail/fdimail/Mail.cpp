#include "Mail.h"


Mail::Mail(const std::string &issuing)
{

}

Mail::Mail(const Mail &originalMail, const std::string &issuing)
{

}

Mail::~Mail()
{

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

