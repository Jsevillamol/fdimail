#ifndef SESSION
#define SESSION

#include "GraphInter.h"
#include "Manager.h"
#include "User.h"
#include "VisibleTrayList.h"

class Mail;

/*
This class is responsible for the user session, 
for what he can do on it
*/

class Session
{
private:
	Manager* manager;
	User* user;

	VisibleTrayList visible;

	bool active_list; //0 for inbox, 1 for outbox
	void changeTray() { active_list = !active_list; }

	void launch();

	void readMail();
	void sendMail();
	void answerMail(Mail* &originalMail);
	void forwardMail(Mail* &originalMail);
	void deleteMail();
	void fastRead();

	void AccountOptions(int &option);
	void AddFastName(User* user);
	void AliasOptions();

	void filterOptions(Filter filter);
	void chooseFilter(Filter filter);
	void chooseOrder(Filter filter);

	void changeUsername();
	void changePassword();

public:

	Session(Manager* manager); //logIn
	~Session();

	Manager* getManager(){ return manager; }
	User* getUser(){ return user; }
	TrayList* active_tray() { return (active_list) ? user->getOutbox() : user->getInbox(); }
	VisibleTrayList* get_visible(){ return &visible; }
	bool get_active_list(){ return active_list; }
};
#endif
