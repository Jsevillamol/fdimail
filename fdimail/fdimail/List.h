#ifndef LIST
#define LIST
#include <assert.h>

//Template for lists
template <class T, int MAX>
class List
{
private:
	T** list;
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

	bool insert(const T &elem);
	bool search(const std::string &id, int &pos) const;

	bool destroy(const std::string &id);
};

template <class T, int MAX>
List<T,MAX>::List() : counter(0)
{
	list = new T*[MAX];
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

	delete[] list;
}

template<class T, int MAX>
bool List<T, MAX>::insert(const T &elem)
{
	if (counter < MAX)
	{
		//Look for corresponding position
		int pos;
		search(elem.getId(), pos)
		//Make space for newcomer
		shiftRight(pos);
		//Insert the elem
		list[pos] = elem;
		counter++;
	}
	else return false;
}

template<class T, int MAX>
void List<T, MAX>::shiftRight(const int pos)
{
	assert(counter < MAX);
	for (int i = counter; i > pos; i--)
	{
		List[i] = List[i - 1];
	}
}

template<class T, int MAX>
bool List<T, MAX>::search(const std::string &id, int &pos) const
{
	int left_key = 0, right_key = counter;
	while (left_key < right_key)
	{
		pos = (left_key + right_key) / 2;
		if (list[pos].getId() == id)
			return true;
		else if (list[pos].getId() < id)
			left_key = pos + 1;
		else
			right_key = pos - 1;
	}
	return false;
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
	assert(0<=pos<counter)
	for (int i = pos; i < counter - 1; i++)
	{
		List[i] = List[i+1];
	}
}

#endif // !LIST
