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
	void orderBySubject();
	void orderByEmissor();

	inline bool full() const  { return this->counter == MAX_ELEMS; }
	inline int length() const { return this->counter; }

	tElemTray* operator [](int i) { return list[i]; }

	void setFilterDate(Date up, Date low)
	{
		filters[date] = true;

		lower = low;

		upper = up;
	}

	void setFilter(std::string search, Filter field)
	{
		filters[field] = true;

		keys[field] = search;
	}

	void closeFilter(Filter field)
	{
		filters[field] = false;
	}

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