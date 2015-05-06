#ifndef CONTACTLIST
#define CONTACTLIST
#include "List.h"
#include "tContact.h"
#include "GlobalConstants.h"

class ContactList : public List < tContact, MAX_FASTNAMES >
{
	//If name is in contacts, returns address associated.
	//Else, it returns name unchanged
	std::string SearchFastName(std::string &name);
};

#endif //CONTACTLIST