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
	bool active_list; //0 for inbox, 1 for outbox
	void changeTray() { active_list = !active_list; }
	TrayList* active_tray() { return (active_list) ?user->getOutbox() :user->getInbox(); }

	Session(Manager* manager); //logIn
	~Session();

	void launch();

	Manager* getManager(){ return manager; }
	User* getUser(){ return user; }

	void readMail();
	void sendMail();
	void answerMail(Mail &originalMail);
	void forwardMail(Mail &originalMail);
	void deleteMail();
	void fastRead();
};
#endif
