#ifndef GRAPHINTER
#define GRAPHINTER
#include "Mail.h"
#include "TrayList.h"
#include "UserList.h"
#include "ContactList.h"
#include <iomanip>
#include <iostream>

/*
Class responsible for interacting with the user
through the console
*/

class Session;
class User;
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
	int mainMenu(); 
	void logMenu(std::string &username, std::string &password);
	int sessionMenu(Session* sesion); 
	std::string selectMail(Session* sesion); 
	std::string selectAlias(Session* session);

	//Mail functions
	int mailMenu(); 
	Mail* newMail(const std::string &sender, ContactList* contactList);
	Mail* answerMail(Mail* &originalMail, const std::string &sender); 
	Mail* forward(Mail* &originalMail, const std::string &sender, ContactList* contactList);
	Mail* errorMail(const std::string &sender);

	//Fastnames
	int FastName(ContactList* contactList);
	void showFastNames(ContactList* contactList);
	
	//Auxiliar funtions
	void drawMail(const Mail* mail);

	std::string valid_user();
	std::string inputBox(std::string &message);
	void display(std::string error);
	void display(char sign);
	void enter(std::string &word);
	void enter(int &digit);
	std::string HideLimitPassword();
	std::string HidePassword();
	void pause();
	void clearConsole();
	int digitBetween(int a, int b);
	int WhatToDelete();
	
	int AccountOptions();
	std::string center_word(std::string number, int length, std::string arround);
	void tab_word(std::string word);
	void checkUsername(std::string &password);
	void checkPassword(std::string &password);
	std::string linea();
};
#endif //GRAPHINTER
