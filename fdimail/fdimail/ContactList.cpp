#include "ContactList.h"

ContactList::ContactList(std::string userID): List()
{
	tContact* me = new tContact(userID, "Me");
	insert(me);
}

std::string ContactList::SearchFastName(std::string &name)
{
	for (int j = 0; j < name.size(); j++)
	{
		if (name[j] == '@')
		{
			return name; //If it has a @ it is a direction
		}
	}

	//Search in contactList
	tContact* contact = get("name");
	if (contact != nullptr) return contact->getAddress();
	//if it is not a direction nor an alias, append @fdimail.com and return
	else return name + "@fdimail.com";
}

void ContactList::changeMe(std::string new_name)
{
	this->get("Me")->alias = new_name;
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
	int n;
	file >> n;

	for (int i = 0; (i < n) && (!file.fail()); i++)
	{
		tContact* cont = new tContact();
		cont->load(file);
		this->insert(cont);
	}
}