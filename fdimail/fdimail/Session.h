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
	Session(Manager* manager, Session* sesion); //logIn
	Session::Session();
	~Session();

	void launch(Session* sesion);

	Manager* getManager(){ return manager; }
	User* getUser(){ return user; }
	Mail* getMail(){ return mail; }

	void readMail(Session* sesion);
	void sendMail();
	void deleteMail();
	void fastRead(Session* sesion);
};
#endif
