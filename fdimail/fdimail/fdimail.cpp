/*-------------------------------
Fdimail
=======

Authors:
Jaime Sevilla Molina.
Victor Gonzalez del Hierro.

Date:
2015/5

Version:
4.0

Features:
Apart from the order in the enunciate of the practice, we have implemented:
	1. A submenu to order or filter the active tray by the paramenter you choose.
	2. A submenu to change your username, password or delete your account.
	3. An option to send, or forward a mail to more than one destinatary.
	4. A subprogram to encript the user password on the savefile.
	5. Detection and correction of errors in data entry console.
	6. A submenu to asign alias to other users, or delete them.
	7. A subprogram to hide the entry console password.
	8. An option to forward a mail.

---------------------------------*/

#include "Manager.h"
#include "Session.h"

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Manager manager("fdimail.com");
	Session session(&manager);
	return 0;
}