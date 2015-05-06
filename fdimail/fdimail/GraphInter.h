#ifndef GRAPHINTER
#define GRAPHINTER
#include "Mail.h"
#include "TrayList.h"
#include <iomanip>
#include <iostream>

/*
Class responsible for interact with the user
through the console
*/

class Session;
//Graphical Interface. May be used to implement SFML, as of now prints through the console
class GraphInter
{
private:
	static GraphInter* inter;
	Session* session;
	GraphInter();//to prevent instantation
public:
	~GraphInter();

	static GraphInter* get();
	static void load();
	static void close();

	//Core functions
	int mainMenu(); 
	void logMenu(std::string &username, std::string &password);
	int sessionMenu(Session* sesion); 
	std::string selectMail(Session* sesion); 
	int mailMenu(); 
	Mail* newMail(const std::string &sender); 
	Mail* answerMail(Mail* &originalMail, const std::string &sender); 
	Mail* forward(Mail* &originalMail, const std::string &sender);
	Mail* errorMail(const std::string &sender);

	//Auxiliar funtions. Implement or not
	void drawMail(const Mail* mail);

	std::string valid_user();
	std::string inputBox(std::string &message);
	void display(std::string error);
	void enter(std::string &word);
	void enter(int &digit);
	void pause();
	void clearConsole();
	int digitBetween(int a, int b);
	int WhatToDelete();
	int AccountOptions();
	std::string center_word(std::string number, int length, std::string arround);
	void tab_word(std::string word);
	std::string changeUsername();
	std::string changePassword();
	void checkUsername(std::string &password);
	void checkPassword(std::string &password);
	std::string linea();
};
#endif //GRAPHINTER
