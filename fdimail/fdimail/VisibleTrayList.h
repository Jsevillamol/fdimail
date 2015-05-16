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

	void init(TrayList* trayList);
	void link(TrayList* trayList);
	void refresh();
	void sync();

	void changeOrder(Filter order){ active_order = order; }

	template<typename Funct, typename K>
	void filterBy(Funct filter, K key);
	void filterByDate(std::string lower, std::string upper);
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

	inline bool full()  const { return this->counter == MAX_ELEMS; }
	inline int length() const { return this->counter; }

	tElemTray* operator [](int i) { return list[i]; }

	void setFilterDate(std::string up, std::string low)
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

	void setFilterRead()
	{
		filters[read] = true;
	}

	void setFilterUnread()
	{
		filters[unread] = true;
	}

	void setInvert()
	{
		inverse_order = !inverse_order;
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

private:

	bool insert(tElemTray* elem);
	void change(int pos1, int pos2);
	void shiftLeft(int pos);
	void erase();

	TrayList* trayList;
	Filter active_order;
	bool inverse_order;

	//Filters
	std::map<Filter, bool> filters;
	std::string lower;
	std::string upper;
	std::map<Filter, std::string> keys;

	int counter;

	tElemTray* list[MAX_ELEMS];
};


#endif