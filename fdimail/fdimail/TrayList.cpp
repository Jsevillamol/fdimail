#include "TrayList.h"
#include "tElemTray.h"

void TrayList::save(std::ofstream &file)const
{
	file << this->counter << std::endl;

	for (int i = 0; i < this->length(); i++)
	{
		this->list[i]->save(file);
	}
}

void TrayList::load(std::ifstream &file)
{
	file >> this->counter;

	for (int i = 0; (i < this->length()) && (!file.fail()); i++)
	{
		tElemTray* elem = new tElemTray();
		elem->load(file);
		this->list[i] = elem;
	}
}

bool TrayList::search(std::string &id, int &pos)
{
	for (pos = 0; pos < this->counter && list[pos]->getId() != id; pos++);
	if (pos < this->counter) return true;
	else return false;
}

void TrayList::insert(tElemTray * const elem)
{
	//std::cout << "Inserting in TrayList the object " << elem << std::endl;
	if (counter == MAX_ELEMS)
	{
		shiftLeft(counter);
		list[counter] = elem;
	}
	else
	{
		list[counter++] = elem;
	}
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
