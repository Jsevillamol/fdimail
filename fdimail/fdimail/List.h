#ifndef LIST
#define LIST
//Probably wont be used, but may be useful to have around
template <T, MAX>
class List
{
private:
	T** list;
	int counter;
public:
	inline void initialize(){ this->counter = 0; }
	inline bool full()const{ return this->counter == MAX; }
	inline int lenght()const{ return this->counter; }
};

#endif // !LIST
