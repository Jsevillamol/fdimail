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
	static void close();

	//Core functions
	int mainMenu(); //Options: sign in and sign up
	void logMenu(std::string &username, std::string &password); //Returns username and password
	int sessionMenu(Session* sesion); //Shows active tray, returns user options (read mail, delete mail, etc)
	std::string selectMail(Session* sesion); //Shows active tray, returns idMail of mail selected
	int mailMenu(); //Shows mail, returns options answer (true) or return to sessionMenu (false)
	Mail* newMail(const std::string &sender); //Returns a full mail
	Mail* answerMail(Mail &originalMail); //Returns an answer mail
	Mail* forward(Mail &originaltMail);

	//Auxiliar funtions. Implement or not
	void drawMail(const Mail* mail);

	std::string valid_user();
	std::string valid_password();
	std::string inputBox(std::string &message);
	void error(std::string error);
	void enter(std::string &word);
	void enter(int &digit);
	void pause();
	void clearConsole(){ system("cls"); }
	int digitBetween(int a, int b);
	int WhatToDelete();
	std::string center_word(std::string number, int lenght, std::string arround);
	void tab_word(std::string word);
	void check_password(std::string& password);
	void linea();
};
#endif //GRAPHINTER
