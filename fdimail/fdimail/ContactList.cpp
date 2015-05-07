#include "ContactList.h"

std::string ContactList::SearchFastName(std::string &name)
{
	bool alias_found = false;
	int i;

	for (int j = 0; j < name.size(); j++)
	{
		if (name[j] == '@')
		{
			return name; //If it has a @ it is a direction
		}
	}

	for (i = 0; i < this->counter && !alias_found; i++)
	{
		if (this->list[i]->getAlias() == name)
		{
			alias_found = true;
		}
	}

	if (alias_found) return this->list[i]->getId();

	else 
	{
		for (int i = 0; i < maillist->length(); i++)
		{
			if (maillist->operator[](i)->getId == name + "@fdimail.com")
			{
				return name + "@fdimail.com";
			}
		}
	}
	return name;
}

void ContactList::save(std::ofstream &file)const
{
	file << this->counter << std::endl;

	for (int i = 0; i < this->counter; i++)
	{
		this->list[i]->save(file);
	}
}

void ContactList::load(std::ifstream &file)
{
	file >> this->counter;

	for (int i = 0; (i < this->counter) && (!file.fail()); i++)
	{
		tContact* cont = new tContact();
		cont->load(file);
		this->list[i] = cont;
	}
}