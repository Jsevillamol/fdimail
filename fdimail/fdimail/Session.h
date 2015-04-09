#ifndef SESSION
#define SESSION

#include "Manager.h"
#include "User.h"

class Session
{
private:
	Manager* manager;
	User* user;
public:
	Session(Manager* new_manager, User* new_user); //logIn
	~Session();

	void readMail();
	void sendMail();
	void terminateMail();
	void fastRead();
};
#endif
