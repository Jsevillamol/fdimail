#include "VisibleTrayList.h"
#include "tElemTray.h"
#include "TrayList.h"
#include "Date.h"

void VisibleTrayList::link(TrayList* trayList)
{
	this->trayList = trayList;
}

void VisibleTrayList::refresh()
{
	sync();

	switch (active_order)
	{
	default:
		orderByDate();
	}
}

void VisibleTrayList::sync(){
	erase();
	for (int i = 0; i < this->trayList->length(); i++){
		insert(trayList->operator[](i));
	}
}

template<typename Funct, typename K>
void VisibleTrayList::filterBy(Funct filter, K key)
{
	erase();
	for (int i = 0; i < this->length(); i++){
		if (!filter(list[i], key)) shiftLeft(i);
	}
}

void VisibleTrayList::filterByDate(Date lower, Date upper){
	filterBy([](tElemTray* a, Date key){
		return key <= a->mail->date;
		},
		lower
	);
	filterBy([](tElemTray* a, Date key){
		return a->mail->date <= key;
		},
		upper
	);
}

void VisibleTrayList::filterBySubject(std::string key){
	filterBy([](tElemTray* a, std::string key){
		return a->mail->subject.find(key) != -1;
		},
		key
	);
}

void VisibleTrayList::filterByBody(std::string key){
	filterBy([](tElemTray* a, std::string key){
		return a->mail->body.find(key) != -1;
		},
		key
	);
}

void VisibleTrayList::filterByEmissor(std::string key){
	filterBy([](tElemTray* a, std::string key){
		return a->mail->from.find(key) != -1;
		},
		key
	);
}

void VisibleTrayList::filterByRecipient(std::string key){
	filterBy([](tElemTray* a, std::string key){
		for (int i = 0; i < a->mail->recipient_count; i++){
			if (a->mail->recipients[i].find(key) != -1)
				return true;
			}
		return false;
		},
		key
	);
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
}

void VisibleTrayList::orderByDate()
{
	orderBy([](tElemTray* a, tElemTray* b){ return a->mail->date < b->mail->date; });
}

void VisibleTrayList::orderByIssue(){
	orderBy(
		[](tElemTray* a, tElemTray* b)
		{ return (a->mail->subject < b->mail->subject);	}
	);
}

void VisibleTrayList::erase()
{
	counter = 0;
}

bool VisibleTrayList::insert(tElemTray* elem)
{
	if (!full())
	{
		list[length()] = elem;
		this->counter++;
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