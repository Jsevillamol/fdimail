#ifndef CONTACTLIST
#define CONTACTLIST
#include "List.h"
#include "tContact.h"
#include "MailList.h"
#include "GlobalConstants.h"

class ContactList : public List < tContact, MAX_FASTNAMES >
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