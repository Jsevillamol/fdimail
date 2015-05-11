#include "VisibleTrayList.h"
#include "tElemTray.h"
#include "TrayList.h"

void VisibleTrayList::link(TrayList* trayList)
{
	this->trayList = trayList;
	unfilter();
}

void VisibleTrayList::refresh(){
	switch (active_filter){
	default:
		unfilter();
	}
}

template<typename Funct, typename K>
void VisibleTrayList::filterBy(Funct filter, K key){
	erase();
	for (int i = 0; i < this->trayList->length(); i++){
		if (filter(trayList->operator[](i), key)) insert(trayList->operator[](i));
	}
}

void VisibleTrayList::unfilter(){
	filterBy(
		[](tElemTray* a, int key){ return true; },
		0
	);
}

template<typename Funct>
void VisibleTrayList::orderBy(Funct order){
	//Bubblesort
	bool change_made;
	do{
		change_made = false;
		for (int i = 0; i < this->length() - 1; i++){
			if (!order(list[i], list[i + 1])){
				this->change(i, i + 1);
				change_made = true;
			}
		}
	} while (change_made);
}

void VisibleTrayList::orderByIssue(){
	orderBy(
		[](tElemTray* a, tElemTray* b){
		if (a->mail->subject != b->mail->subject){
			return (a->mail->subject < b->mail->subject);
		}
		else return (a->mail->date) < (b->mail->date);
	}
	);
}

void VisibleTrayList::erase(){
	counter = 0;
}

bool VisibleTrayList::insert(tElemTray* elem){
	if (!full()){
		list[length()] = elem;
		this->counter++;
		return true;
	}
	else return false;
}

void VisibleTrayList::change(int pos1, int pos2){
	tElemTray* aux = list[pos1];
	list[pos1] = list[pos2];
	list[pos2] = aux;
}