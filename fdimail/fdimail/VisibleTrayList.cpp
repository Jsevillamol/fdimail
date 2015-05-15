#include "VisibleTrayList.h"
#include "tElemTray.h"
#include "TrayList.h"
#include "Date.h"

VisibleTrayList::VisibleTrayList()
{
	filters[date] = false;
	filters[Filter::subject] = false;
	filters[Filter::body] = false;
	filters[Filter::emissor] = false;
	filters[Filter::recipients] = false;

	active_order = none;
}

void VisibleTrayList::link(TrayList* trayList)
{
	this->trayList = trayList;
}

void VisibleTrayList::refresh()
{
	sync();
	
	//Apply activated filters
	if (filters[date])				filterByDate(lower, upper);
	if (filters[Filter::subject])	filterBySubject(keys[subject]);
	if (filters[Filter::body])		filterByBody(keys[body]);
	if (filters[Filter::emissor])	filterByEmissor(keys[emissor]);
	if (filters[Filter::recipients])filterByRecipient(keys[recipients]);
	if (filters[Filter::read])      filterByRead(true);
	if (filters[Filter::unread])    filterByRead(false);

	//Apply order
	switch (active_order)
	{
	case subject:
		orderBySubject();
		break;
	case emissor:
		orderByEmissor();
		break;
	default:
		orderByDate();
		break;
	}

	if (inverse_order) reverse();
}

void VisibleTrayList::sync()
{
	erase();
	for (int i = 0; i < this->trayList->length(); i++){
		insert(trayList->operator[](i));
	}
}

template<typename Funct, typename K>
void VisibleTrayList::filterBy(Funct filter, K key)
{
	//erase();
	for (int i = 0; i < this->length(); i++)
	{
		if (!filter(list[i], key))
		{
			shiftLeft(i);
			list[counter] = nullptr;
			counter--;
			i--;
		}
	}
}

void VisibleTrayList::filterByDate(Date lower, Date upper)
{
	filterBy([](tElemTray* a, Date key){ return key <= a->mail->date; }, lower);
	filterBy([](tElemTray* a, Date key){ return a->mail->date <= key; }, upper);
}

void VisibleTrayList::filterBySubject(std::string key)
{
	filterBy([](tElemTray* a, std::string key){ return a->mail->subject.find(key) != -1; }, key);
}

void VisibleTrayList::filterByBody(std::string key)
{
	filterBy([](tElemTray* a, std::string key){ return a->mail->body.find(key) != -1; }, key);
}

void VisibleTrayList::filterByEmissor(std::string key)
{
	filterBy([](tElemTray* a, std::string key){ return a->mail->from.find(key) != -1; }, key);
}

void VisibleTrayList::filterByRecipient(std::string key)
{
	filterBy([](tElemTray* a, std::string key){ for (int i = 0; i < a->mail->recipient_count; i++){ if (a->mail->recipients[i].find(key) != -1) return true; } return false; }, key);
}

void VisibleTrayList::filterByRead(bool is_read)
{
	filterBy([](tElemTray* a, bool is_read) { return a->read == is_read; }, is_read);
}

template<typename Funct>
void VisibleTrayList::orderBy(Funct order)
{
	//Bubblesort
	bool change_made;

	do{
		change_made = false;
		for (int i = 0; i < this->length() - 1; i++)
		{
			if (!order(list[i], list[i + 1]))
			{
				this->change(i, i + 1);
				change_made = true;
			}
		}
	} while (change_made);
	setInvert();
}

void VisibleTrayList::orderByDate()
{
	orderBy([](tElemTray* a, tElemTray* b){ return a->mail->date < b->mail->date; });
}

void VisibleTrayList::orderBySubject()
{
	orderBy([](tElemTray* a, tElemTray* b) { return (a->mail->getsubject() < b->mail->getsubject()); });
}

void VisibleTrayList::orderByEmissor()
{
	orderBy([](tElemTray* a, tElemTray* b) { return (a->mail->from < b->mail->from);} );
}

void VisibleTrayList::orderByRecipient()
{
	orderBy([](tElemTray* a, tElemTray* b) { return (a->mail->recipients[0] < b->mail->recipients[0]); });
}

void VisibleTrayList::orderByBody()
{
	orderBy([](tElemTray* a, tElemTray* b) { return (a->mail->body < b->mail->body); });
}

void VisibleTrayList::reverse()
{
	for (int i = 0; i < length() / 2; i++)
	{
		change(i, length() - i - 1);
	}
}

void VisibleTrayList::erase()
{
	for (int i = 0; i < length(); i++)
	{
		list[i] = nullptr;
	}
	counter = 0;
}

bool VisibleTrayList::insert(tElemTray* elem)
{
	if (!full())
	{
		list[length()] = elem;
		counter++;
		return true;
	}
	else return false;
}

void VisibleTrayList::change(int pos1, int pos2)
{
	tElemTray* aux = list[pos1];
	list[pos1] = list[pos2];
	list[pos2] = aux;
}

void VisibleTrayList::shiftLeft(int pos){
	assert(0 <= pos && pos < counter);
	for (int i = pos; i < counter - 1; i++)
	{
		list[i] = list[i + 1];
	}
}