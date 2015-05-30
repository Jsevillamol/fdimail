#ifndef TRAYLIST
#define TRAYLIST
#include <fstream>
#include "List.h"
#include "tElemTray.h"
#include "GlobalConstants.h"

/*----------------------------
Derived class from list, responsible
for work whith the id of the mails, 
and its read status
------------------------------*/

class TrayList: public List<tElemTray>
{
public:
	//Overrides
	tElemTray* get(const std::string &id);
	bool search(const std::string &id, int &pos);
	void insert(tElemTray * const elem);
	bool destroy(const std::string &id);

	void save(std::ofstream &file)const;
	void load(std::ifstream &file);

	//Class Exclusive
	bool readMail(const std::string &idMail);
};
#endif