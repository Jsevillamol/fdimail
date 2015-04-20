#ifndef GRAPHINTER
#define GRAPHINTER
#include "Mail.h"
#include "TrayList.h"
#include <iomanip>
#include <iostream>

class Session;
//Graphical Interface. May be used to implement SFML, as of now prints through the console
class GraphInter
{
private:
	static GraphInter* inter;
	GraphInter();//to prevent instantation
public:
	~GraphInter();

	static GraphInter* get();
	static void load();

	//Core functions
	int mainMenu(); //Options: sign in and sign up
	void logMenu(std::string &username, std::string &password); //Returns username and password
	int sessionMenu(Session* sesion); //Shows active tray, returns user options (read mail, delete mail, etc)
	std::string selectMail(Session* sesion); //Shows active tray, returns idMail of mail selected
	bool mailMenu(); //Shows mail, returns options answer (true) or return to sessionMenu (false)
	Mail* newMail(const std::string &sender); //Returns a full mail
	Mail* answerMail(Mail &originalMail); //Returns an answer mail

	//Auxiliar funtions. Implement or not
	void drawMail(const Mail* mail);

	std::string valid_user();
	std::string valid_password();
	std::string inputBox(std::string &message);
	void pause();
	int digitBetween(int a, int b);
	std::string center_word(std::string number, int lenght);
	void check_password(std::string& password);
	void linea();
};
#endif //GRAPHINTER
