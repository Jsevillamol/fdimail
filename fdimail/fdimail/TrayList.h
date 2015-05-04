#ifndef TRAYLIST
#define TRAYLIST
#include <fstream>
#include "List.h"
#include "tElemTray.h"
#include "GlobalConstants.h"

class TrayList: public List<tElemTray, MAX_ELEMS>
{
public:
	void save(std::ofstream &file)const;
	void load(std::ifstream &file);

	bool search(std::string &id, int &pos);

	void insert(tElemTray * const elem);

	bool readMail(const std::string &idMail);
};
#endif
