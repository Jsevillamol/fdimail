#include "TrayList.h"
#include "tElemTray.h"

void TrayList::save(std::ofstream &file)const
{
	file << this->counter << std::endl;

	for (int i = 0; i < this->lenght(); i++)
	{
		this->list[i]->save(file);
	}
}

void TrayList::load(std::ifstream &file)
{
	file >> this->counter;

	for (int i = 0; (i < this->lenght()) && (!file.fail()); i++)
	{
		tElemTray* elem = new tElemTray();
		elem->load(file);
		this->list[i] = elem;
	}
}

bool TrayList::insert(tElemTray * const elem)
{
	//std::cout << "Inserting in TrayList the object " << elem << std::endl;
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
