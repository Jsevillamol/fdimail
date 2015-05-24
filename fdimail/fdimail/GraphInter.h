#ifndef GRAPHINTER
#define GRAPHINTER
#include "Mail.h"
#include "Filters.h"
#include "TrayList.h"
#include "UserList.h"
#include "ContactList.h"
#include "Filters.h"
#include <iomanip>
#include <iostream>

/*
Class responsible for interacting with the user
through the console
*/

class Session;
class User;

class GraphInter
{
public:
	~GraphInter() {}

	static GraphInter* get();
	static void load();
	static void close();
	
	//Menus
	int mainMenu(); 
	void logMenu(std::string &username, std::string &password);
	int sessionMenu(Session* sesion); 
	Mail* selectMail(Session* sesion); 
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
	void showTray(Session* session);

	std::string valid_user();
	
	void choose(std::string parameter, Filter &filter, Session* session);
	int filter();
	void pause();
	void clearConsole();
	
	int WhatToDelete();
	int Invert();
	
	int AccountOptions();

	//Input
	void checkUsername(std::string &password);
	void checkPassword(std::string &password);

	void enter(std::string &word);
	void enter(int &digit);
	void enter(char* str);

	std::string HideLimitPassword();
	std::string HidePassword();

	//Outout
	void display(std::string error);
	void display(char sign);

private:
	static GraphInter* inter;
	GraphInter() {}//to prevent instantation

	//Auxiliar input functions
	void send_to_multiple(Mail* mail, ContactList* contactList);

	int digitBetween(int a, int b);

	//Formatting strings
	std::string center_word(std::string number, int length, std::string arround);
	void tab_word(std::string word);
	std::string linea();
};
#endif //GRAPHINTER
