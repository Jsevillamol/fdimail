#include "Manager.h"
#include "Session.h"
int main() 
{
	Manager manager("fdimail.com");
	Session session(&manager);
	return 0;
}