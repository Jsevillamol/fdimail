#ifndef TRAYLIST
#define TRAYLIST
#include <fstream>
#include "List.h"
#include "tElemTray.h"
#include "GlobalConstants.h"

/*
Derived class from list, responsible
for work whith the id of the mails, 
and its read status
*/

class TrayList: public List<tElemTray, MAX_ELEMS>
{
public:
	//Overrides
	tElemTray* get(std::string &id);
	bool search(std::string &id, int &pos);
	void insert(tElemTray * const elem);

	void save(std::ofstream &file)const;
	void load(std::ifstream &file);

	//Class Exclusive
	bool readMail(const std::string &idMail);

};


#endif
