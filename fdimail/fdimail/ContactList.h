#ifndef CONTACTLIST
#define CONTACTLIST

#include "GlobalConstants.h"
#include "tContact.h"
#include "MailList.h"
#include "List.h"

/*----------------------------
Derived class from list, responsible
for work whith the alias an user has
------------------------------*/

class ContactList : public List < tContact>
{
public:
	ContactList(){}
	ContactList(std::string userID);

	//If name is in contacts, returns address associated.
	//Else, it returns name unchanged
	std::string SearchFastName(std::string &name);
	void changeMe(std::string new_name);

	void save(std::ofstream &file)const;
	void load(std::ifstream &file);
};

#endif //CONTACTLIST