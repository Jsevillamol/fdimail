#ifndef VISIBLETRAYLIST
#define VISIBLETRAYLIST
#include "GlobalConstants.h"
#include "Filters.h"
#include "Date.h"
#include <string>
#include <map>

struct tElemTray;
class TrayList;

class VisibleTrayList
{
public:
	VisibleTrayList();

	void link(TrayList* trayList);
	void refresh();
	void sync();

	void changeOrder(Filter order){ active_order = order; }

	template<typename Funct, typename K>
	void filterBy(Funct filter, K key);
	void filterByDate(Date lower, Date upper);
	void filterBySubject(std::string key);
	void filterByBody(std::string key);
	void filterByEmissor(std::string key);
	void filterByRecipient(std::string key);

	template<typename Funct>
	void orderBy(Funct order);
	void orderByDate();
	void orderByIssue();

	inline bool full() const  { return this->counter == MAX_ELEMS; }
	inline int length() const { return this->counter; }

	tElemTray* operator [](int i) { return list[i]; }

private:

	bool insert(tElemTray* elem);
	void change(int pos1, int pos2);
	void shiftLeft(int pos);
	void erase();

	TrayList* trayList;
	Filter active_order;

	//Filters
	std::map<Filter, bool> filters;
	Date lower;
	Date upper;
	std::map<Filter, std::string> keys;

	int counter;

	tElemTray* list[MAX_ELEMS];
};


#endif