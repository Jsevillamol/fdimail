#ifndef LIST
#define LIST
#include <assert.h>
#include <iostream>

/*
This is a base class for all the list this program has
We have used a template to be able to work whith diferent
types of arguments
*/

//Template for lists
template <class T, int MAX>
class List
{
public:
	List() : counter(0) {}
	~List();

	inline bool full() const  { return this->counter == MAX; }
	inline int length() const { return this->counter; }

	T* operator [](int i) { return list[i]; }

	bool insert(T* elem);
	bool destroy(const std::string &id);

	void erase();

	bool search(const std::string &id, int &pos) const;
	T* get(const std::string &id);

	void save(const std::string &name);
	bool load(const std::string &name/*, const std::string &url*/);

protected:
	T* list[MAX];
	int counter;

	//Moves the list one space right from pos to end
	void shiftRight(const int pos);
	//Eliminates pointer in pos
	void shiftLeft(const int pos);
};

template<class T, int MAX>
List<T, MAX>::~List()
{
	erase();
}

//It search the position where an element should be,
//makes space for him, and inserts it in this position
template<class T, int MAX>
bool List<T, MAX>::insert(T* elem)
{
	if (counter < MAX)
	{
		//Look for corresponding position
		int pos;
		search(elem->getId(), pos);
		//Make space for newcomer
		shiftRight(pos);
		//Insert the elem
		list[pos] = elem;
		counter++;
		return true;
	}
	else return false;
}

//Searchs for the element you choose
//on the list, and deletes it
template<class T, int MAX>
bool List<T, MAX>::destroy(const std::string &id)
{
	int pos;
	if (search(id, pos))
	{
		delete list[pos];
		shiftLeft(pos);
		counter--;
		return true;
	}
	else return false;
}

template<class T, int MAX>
void List<T, MAX>::erase()
{
	for (int i = 0; i < this->counter; i++)
	{
		delete list[i];
		list[i] = nullptr;
	}
	this->counter = 0;
}

//Searchs the position where 
//an element should be
template<class T, int MAX>
bool List<T, MAX>::search(const std::string &id, int &pos) const
{
	int left_key = 0, right_key = counter - 1;
	pos = (left_key + right_key) / 2;
	while (left_key <= right_key)
	{
		if (list[pos]->getId() == id)
		{
			return true;
		}
		else if (list[pos]->getId() < id)
		{
			left_key = pos + 1;
		}
		else //if id < list[pos]->getId()
		{
			right_key = pos - 1;
		}
		pos = (left_key + right_key) / 2;
	}
	pos = left_key;
	return false;
}

//Using the id of an element, searchs it 
//on the list and returns the position 
//where it is placed
template<class T, int MAX>
T* List<T, MAX>::get(const std::string &id)
{
	int pos = 0;
	if (search(id, pos))
	{
		return list[pos];
	}
	else
	{
		return nullptr;
	}
}

//Saves all the elements of the list on the
//file you choose, and put the scentinel at
//the end of the file
template<class T, int MAX>
void List<T, MAX>::save(const std::string &name)
{
	std::ofstream file;

	file.open(name);

	for (int i = 0; i < this->length(); i++)
	{
		this->list[i]->save(file);
	}

	file << "XXX";

	file.close();
}

//Loads the elemrnts of the list
//from the file you choose
template<class T, int MAX>
bool List<T, MAX>::load(const std::string &name)
{
	std::ifstream file;
	bool right;
	T* elem;

	file.open(name);

	if (file.is_open())
	{
		right = true;

		for (int i = 0; (i < MAX) && (right); i++)
		{
			elem = new T;

			if (!elem->load(file)) right = false;

			else this->insert(elem);
		}

		file.close();

		return true;
	}
	else return false;
}

//It moves every elemnts on the list
//to the right from the position you choose
template<class T, int MAX>
void List<T, MAX>::shiftRight(const int pos)
{
	assert(counter < MAX);
	for (int i = counter; i > pos; i--)
	{
		list[i] = list[i - 1];
	}
}

//It moves every elemnts on the list
//to the right from the position you choose
template<class T, int MAX>
void List<T, MAX>::shiftLeft(const int pos)
{
	assert(0 <= pos && pos < counter);
	for (int i = pos; i < counter - 1; i++)
	{
		list[i] = list[i+1];
	}
}
#endif // !LIST
