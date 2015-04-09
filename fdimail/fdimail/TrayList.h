#ifndef TRAYLIST
#define TRAILIST
#include <fstream>
#include "tElemTray.h"
#include "GlobalConstants.h"

class TrayList
{
private:
	int counter;
	tElemenTray** list;
public:
	TrayList();
	~TrayList();

	inline bool full()const{ return this->counter == MAX_ELEMS; }
	inline int lenght()const{ return this->counter; }

	void save(std::ofstream &file)const;
	void load(std::ifstream &file);

	bool insert(const tElemenTray &elem);
	int search(const std::string &idMail)const;

	bool terminate(const std::string &idMail);
	bool readMail(const std::string &idMail);
};
#endif
