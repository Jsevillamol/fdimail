#ifndef SESSION
#define SESSION

#include "GraphInter.h"
#include "Manager.h"
#include "User.h"
#include "Mail.h"

class Session
{
private:
	Manager* manager;
	User* user;
public:
	Session(Manager* manager); //logIn
	Session(){}

	void launch();

	Manager* getManager(){ return manager; }
	User* getUser(){ return user; }

	void readMail();
	void sendMail();
	void deleteMail();
	void fastRead();
};
#endif
