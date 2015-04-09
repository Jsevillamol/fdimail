#ifndef TRAYLIST
#define TRAILIST
#include <fstream>
#include "List.h"
#include "tElemTray.h"
#include "GlobalConstants.h"

class TrayList: public List<tElemTray, MAX_ELEMS>
{
public:
	void save(std::ofstream &file)const;
	void load(std::ifstream &file);

	bool readMail(const std::string &idMail);
};
#endif
