#include "Session.h"


Session::Session(Manager* manager):
manager(manager)
{
	//Aqui menu ppal
	user = manager->createAccount();
}


Session::~Session()
{

}

void Session::readMail()
{
	
}

void Session::sendMail()
{

}

void Session::terminateMail()
{

}

void Session::fastRead()
{

}
