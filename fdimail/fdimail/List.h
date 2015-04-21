#ifndef LIST
#define LIST
#include <assert.h>
#include <iostream>
//Template for lists
template <class T, int MAX>
class List
{
protected:
	T* list [MAX];
	int counter;

	//Moves the list one space right from pos to end
	void shiftRight(const int pos);
	//Eliminates pointer in pos
	void shiftLeft(const int pos);
public:
	List();
	~List();

	inline bool full() const  { return this->counter == MAX; }
	inline int lenght() const { return this->counter; }

	bool insert(T* const elem);
	bool search(const std::string &id, int &pos) const;
	T* get(const std::string &id);
	bool destroy(const std::string &id);
	void save(const std::string &name);
	bool load(const std::string &name);

	T* operator [](int i) { return list[i]; }
};

template <class T, int MAX>
List<T,MAX>::List() : counter(0)
{
	for (int i=0; i < MAX; i++)
	{
		list[i] = nullptr;
	}
}

template<class T, int MAX>
List<T, MAX>::~List()
{
	for (int i=0; i < counter; i++)
	{
		delete list[i];
		list[i] = nullptr;
	}

}

template<class T, int MAX>
bool List<T, MAX>::insert(T* const elem)
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

template<class T, int MAX>
void List<T, MAX>::shiftRight(const int pos)
{
	assert(counter < MAX);
	for (int i = counter; i > pos; i--)
	{
		list[i] = list[i - 1];
	}
}

template<class T, int MAX>
bool List<T, MAX>::search(const std::string &id, int &pos) const
{
	int left_key = 0, right_key = counter;
	pos = 0;
	while (left_key < right_key)
	{
		pos = (left_key + right_key) / 2;
		if (list[pos]->getId() == id)
			return true;
		else if (list[pos]->getId() < id)
			left_key = pos + 1;
		else
			right_key = pos - 1;
	}
	return false;
}

template<class T, int MAX>
T* List<T, MAX>::get(const std::string &id)
{
	int pos;
	if (search(id, pos)){
		std::cout << "Found!" << std::endl;
		return list[pos];
	}
	else return nullptr;
}

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
void List<T, MAX>::shiftLeft(const int pos)
{
	assert(0 <= pos && pos < counter);
	for (int i = pos; i < counter - 1; i++)
	{
		list[i] = list[i+1];
	}
}

template<class T, int MAX>
void List<T, MAX>::save(const std::string &name)
{
	std::ofstream file;

	file.open(name);

	for (int i = 0; i < this->lenght(); i++)
	{
		this->list[i]->save(file);
	}

	file << "XXX";

	file.close();
}

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

			list[counter++] = elem;
		}

		return right;
	}
	else return false;
}
#endif // !LIST
