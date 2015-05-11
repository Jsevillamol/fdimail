#include "TrayList.h"
#include "tElemTray.h"
#include "Manager.h"

//Saves all the elements on the you choose
void TrayList::save(std::ofstream &file)const
{
	file << this->counter << std::endl;

	for (int i = 0; i < this->length(); i++)
	{
		this->list[i]->save(file);
	}
}

//Load all elements from the file you choose
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

//Searchs the position of the element you choose
//Returns true if found it, fasle if not
bool TrayList::search(std::string &id, int &pos)
{
	for (pos = 0; pos < this->counter && list[pos]->getId() != id; pos++);
	if (pos < this->counter) return true;
	else return false;
}

//Inserts the element you choose at the end of the list
//If the list is full, deletes the first element, and
//move the rest to the left, and insert the new one
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

//Changes the read status of a mail, from 
//'not read' to 'read', when you read it
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
