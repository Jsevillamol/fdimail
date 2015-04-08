#include "TrayList.h"


TrayList::TrayList()
{

}


TrayList::~TrayList()
{

}

void TrayList::save(std::ofstream &file)const
{

}

void TrayList::load(std::ifstream &file)
{

}

bool TrayList::insert(const tElemenTray &elem)
{
	return true; //Placeholder
}

int TrayList::search(const std::string &idMail)const
{
	return -1; //Placeholder
}

bool TrayList::terminate(const std::string &idMail)
{
	return true; //Placeholder
}

bool TrayList::readMail(const std::string &idMail)
{
	return true; //Placeholder
}