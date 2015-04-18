#ifndef SESSION
#define SESSION

#include "Manager.h"
#include "User.h"
#include "Mail.h"

class Session
{
private:
	Manager* manager;
	User* user;
	Mail* mail;
public:
	Session(Manager* manager); //logIn
	Session();
	~Session();

	void launch();

	Manager* getManager(){ return manager; }
	User* getUser(){ return user; }
	Mail* getMail(){ return mail; }

	void readMail();
	void sendMail();
	void deleteMail();
	void fastRead();
};
#endif
