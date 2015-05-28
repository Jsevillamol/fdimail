/*-------------------------------
Fdimail
=======

Authors:
Jaime Sevilla Molina.
Victor Gonzalez del Hierro.

Date:
2015/5

Version:
6.0

Features:
Apart from the order in the enunciate of the practice, we have implemented:
	 1. A sistem to interact with the console usig the arrows, and the (ENTER) and (ESCAPE) keys.
	 2. A submenu to order or filter the active tray by the paramenter you choose.
	 3. A submenu to change your username, password or delete your account.
	 4. A sistem of pages for show the active tray, with 5 mails per page.
	 5. An option to send, or forward a mail to more than one destinatary.
	 6. A subprogram to encript the user password on the savefile.
	 7. Detection and correction of errors in data entry console.
	 8. A submenu to asign alias to other users, or delete them.
	 9. A subprogram to hide the entry console password.
	10. An option to forward a mail.
	
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