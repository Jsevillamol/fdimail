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
	int menu(std::string elems[], int max_elems, std::string to_choose);
	int aliasMenu(Session* session);
	int trayMenu(Session* session, std::string elems[], int max_elems);
	int mailMenu(Session* session);
	int menumail(Mail* mail, std::string elems[], int max_elems, std::string to_choose);
	int AliasMenu(Session* session);

	int mainMenu(); 
	void logMenu(std::string &username, std::string &password);
	int sessionMenu(Session* sesion); 
	Mail* selectMail(Session* sesion); 
	std::string selectAlias(Session* session);

	//Mail functions
	int mailMenu(Mail* mail); 
	Mail* newMail(const std::string &sender, ContactList* contactList);
	Mail* answerMail(Mail* &originalMail, const std::string &sender); 
	Mail* forward(Mail* &originalMail, const std::string &sender, ContactList* contactList);

	//Fastnames
	void showFastNames(ContactList* contactList);
	
	//Auxiliar funtions
	void drawMail(const Mail* mail);
	void showTray(Session* session);

	std::string valid_user();
	
	int choosefilter(Session* session);
	int chooseorder(Session* session);
	int filter();
	void pause();
	void clearConsole();
	
	int WhatToDelete(Session* session);
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
	static Mail* error;
	static Mail* errorMail();

	GraphInter() {}//to prevent instantation

	//Auxiliar input functions
	void send_to_multiple(Mail* mail, ContactList* contactList);

	int digitBetween(int a, int b);

	int update(int key, int &elem, int max_elems);
	void updateTray(int key, Session* session);

	//Formatting strings
	std::string center_word(std::string number, int length, std::string arround);
	void tab_word(std::string word, int pos, int cont);
	std::string linea();
	std::string pags(Session* session);
};
#endif //GRAPHINTER
