#ifndef LIST
#define LIST
//Probably wont be used, but may be useful to have around
template <class T, int MAX>
class List
{
private:
	T** list;
	int counter;
public:
	List();
	~List();

	inline bool full()const{ return this->counter == MAX; }
	inline int lenght()const{ return this->counter; }

	bool insert(const T &elem);
	bool search(const std::string &id, int &pos)const;

	bool destroy(const std::string &id);
};

template <T, MAX>
List::List() : counter(0)
{
	list = new T*[MAX];
	for (int i; i < MAX; i++)
	{
		list[i] = nullptr;
	}
}

template<T, MAX>
List::~List()
{
	for (int i; i < counter; i++)
	{
		delete list[i];
		list[i] = nullptr;
	}

	delete list;
}

#endif // !LIST
