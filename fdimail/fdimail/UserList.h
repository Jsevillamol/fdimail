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

	inline bool full()const{ return this->counter == MAX_USERS; }
	inline int lenght()const{ return this->counter; }
	bool load(const std::string &name);
	void save(const std::string &name);
	bool insert(const User &user);
	bool search(const std::string &idUser, int &place);
};
#endif
