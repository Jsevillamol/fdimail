#ifndef VISIBLETRAYLIST
#define VISIBLETRAYLIST
#include "List.h"
#include "GlobalConstants.h"
#include "Filters.h"

struct tElemTray;
class TrayList;

class VisibleTrayList :
	public List <tElemTray, MAX_ELEMS>
{
public:
	void link(TrayList* trayList);
	void refresh();

	void changeFilter(Filter filter){ active_filter = filter; }
	template<typename Funct, typename K>
	void filterBy(Funct filter, K key);
	void unfilter();

	template<typename Funct>
	void orderBy(Funct order);

	void orderByIssue();

private:
	bool insert(tElemTray* elem);
	void change(int pos1, int pos2);
	void erase();

	TrayList* trayList;
	Filter active_filter;
};


#endif