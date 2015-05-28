#ifndef VISIBLETRAYLIST
#define VISIBLETRAYLIST
#include "List.h"
#include "GlobalConstants.h"
#include "tElemTray.h"
#include "TrayList.h"
#include "Filters.h"
#include "Date.h"
#include <string>
#include <map>

/*----------------------------
Unordered list of tElemTrays (email references), with capacity to apply filters, orders and easily extendible.
The main method is refresh, which performs a sync (loading every element in the linked TrayList),
applies fliters, orders (bubble sort), and finally discards every element but those of the current page.

Setters are provided to change the filters and sort order applied.
Suborders may be achived by calling the order methods in the proper order (pun not intended).
------------------------------*/

class VisibleTrayList: public List<tElemTray>
{
public:
	VisibleTrayList();

	void init(TrayList* trayList);
	void link(TrayList* trayList); //Sets a new traylist to get elements from
	void refresh(); //Syncs and applies active filters + order + active_page
	void sync(); //Loads every element of the linked trayList

	void changeOrder(Filter order){ active_order = order; }

	template<typename Funct, typename K>
	void filterBy(Funct filter, K key);
	void filterByDate(Date lower, Date upper);
	void filterBySubject(std::string key);
	void filterByBody(std::string key);
	void filterByEmissor(std::string key);
	void filterByRecipient(std::string key);
	void filterByRead(bool is_read);

	template<typename Funct>
	void orderBy(Funct order);
	void orderByDate();
	void orderBySubject();

	void reverse();

	void filterPage(); //Only elements in the active page remain after calling this method.

	tElemTray* operator [](int i) { return list[i]; }

	void setFilterDate(char* up, char* low)
	{
		filters[date] = true;

		Date update = turnDate(up);
		Date lowdate = turnDate(low);

		lower = update;
		upper = lowdate;
	}

	void setFilter(std::string search, Filter field)
	{
		filters[field] = true;
		keys[field] = search;
	}

	void setFilterRead()
	{
		filters[read] = true;
	}

	void setFilterUnread()
	{
		filters[unread] = true;
	}

	void setInvert(bool invert)
	{
		inverse_order = invert;
	}

	void closeFilter() //Desactivates every filter
	{
		for (int i = Filter::subject; i <= Filter::unread; i++)
		{
			filters[Filter(i)] = false;
		}
	}

	int getPage(){ return page; }
	int getLastPage(){ return lastPage; }
	bool LastPage(){ return page == lastPage; }
	void increasePage(){ page++; }
	void decreasePage(){ page--; }

private:

	void insert(tElemTray* elem);
	void change(int pos1, int pos2);

	TrayList* trayList;
	Filter active_order;
	bool inverse_order;

	int page;
	int lastPage;

	//Filters
	std::map<Filter, bool> filters;
	Date lower;
	Date upper;
	std::map<Filter, std::string> keys;
};
#endif