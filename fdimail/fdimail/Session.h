#ifndef SESSION
#define SESSION

#include "Manager.h"
#include "User.h"

class Session
{
public:
	Session();
	~Session();

	bool logIn(Manager* manager, User* user);
	void readMail();
	void sendMail();
	void terminateMail();
	void fastRead();
};
#endif
