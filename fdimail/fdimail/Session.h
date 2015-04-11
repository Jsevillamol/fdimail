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
	Session(Manager* manager); //logIn
	~Session();

	void readMail();
	void sendMail();
	void deleteMail();
	void fastRead();
};
#endif
