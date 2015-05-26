#ifndef VISIBLETRAYLIST
#define VISIBLETRAYLIST
#include "List.h"
#include "GlobalConstants.h"
#include "Filters.h"
#include "Date.h"
#include <string>
#include <map>

struct tElemTray;
class TrayList;

class VisibleTrayList: public List<tElemTray>
{
public:
	VisibleTrayList();

	void init(TrayList* trayList);
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
	void filterByRead(bool is_read);

	template<typename Funct>
	void orderBy(Funct order);
	void orderByDate();
	void orderBySubject();

	void reverse();

	void filterPage();

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

	void closeFilter()
	{
		for (int i = Filter::subject; i <= Filter::unread; i++)
		{
			if (filters[Filter(i)] == true)
			{
				filters[Filter(i)] = false;
			}
		}
	}

	int getPage(){ return page; }

	void increasePage(){ page++; }
	void decreasePage(){ page--; }

private:

	void insert(tElemTray* elem);
	void change(int pos1, int pos2);

	TrayList* trayList;
	Filter active_order;
	bool inverse_order;

	int page;

	//Filters
	std::map<Filter, bool> filters;
	Date lower;
	Date upper;
	std::map<Filter, std::string> keys;
};


#endif
