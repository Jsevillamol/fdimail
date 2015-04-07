#ifndef USERLIST
#define USERLIST

#include <string>
#include "User.h"

class UserList
{
private:
	int counter;
public:
	UserList();
	~UserList();

	inline void initialize(){ this->counter = 0; }
	inline bool full()const{ this->counter == MAX_USERS; }
	inline int lenght()const{ return this->counter; }
	bool load(const std::string &name);
	void save(const std::string &name);
	bool imput(const User &user);
	bool search(const std::string &idUser, int &place);
};
#endif
