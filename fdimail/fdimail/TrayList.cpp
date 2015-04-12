#include "TrayList.h"

void TrayList::save(std::ofstream &file)const
{

}

void TrayList::load(std::ifstream &file)
{

}

bool TrayList::insert(tElemTray * const elem)
{
	if (counter < MAX_ELEMS)
	{
		list[counter++] = elem;
		return true;
	}
	else return false;
}

bool TrayList::readMail(const std::string &idMail)
{
	tElemTray* elem = get(idMail);
	if (elem != nullptr)
	{
		elem->read = true;
		return true;
	}
	else return false;
}
