#ifndef GRAPHINTER
#define GRAPHINTER
#include "Mail.h"
#include "TrayList.h"
#include "Session.h"
#include <iomanip>
#include <iostream>

//Graphical Interface. May be used to implement SFML, as of now prints through the console
class GraphInter
{
private:
	static GraphInter* inter;
	GraphInter(); //to prevent instantation
public:
	~GraphInter();

	static GraphInter* get();
	static void load();

	int drawMail(const Mail* mail, Session* sesion);
	void drawTraylist(TrayList* list);
	void drawHeader(const Mail* mail);
	void showText(std::string &text);

	User regist(User* user);
	std::string valid_user();
	std::string valid_password();

	int logMenu();
	int mainMenu(Session* sesion);
	bool mailMenu();
	std::string inputBox(std::string &message);
	std::string selectMail(TrayList* tray);

	void pause();
	int digitBetween(int a, int b);
	std::string center_word(std::string number, int lenght);
	void linea();
};
#endif //GRAPHINTER
