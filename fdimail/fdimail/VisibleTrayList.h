#ifndef VISIBLETRAYLIST
#define VISIBLETRAYLIST
#include "GlobalConstants.h"
#include "Filters.h"

struct tElemTray;
class TrayList;

class VisibleTrayList
{
public:
	//VisibleTrayList();

	void link(TrayList* trayList);
	void refresh();

	void changeFilter(Filter filter){ active_filter = filter; }
	template<typename Funct, typename K>
	void filterBy(Funct filter, K key);
	void unfilter();

	template<typename Funct>
	void orderBy(Funct order);

	void orderByIssue();

	inline bool full() const  { return this->counter == MAX_ELEMS; }
	inline int length() const { return this->counter; }

	tElemTray* operator [](int i) { return list[i]; }

private:

	bool insert(tElemTray* elem);
	void change(int pos1, int pos2);
	void erase();

	TrayList* trayList;
	Filter active_filter;

	int counter;

	tElemTray* list[MAX_ELEMS];
};


#endif