#include "GraphInter.h"
#include <iostream>

GraphInter* GraphInter::inter = nullptr;

GraphInter::GraphInter()
{
}


GraphInter::~GraphInter()
{
}

GraphInter* GraphInter::get()
{
	return inter;
}

void GraphInter::load()
{
	if (inter = nullptr) inter = new GraphInter;
}

void drawMail(const Mail* mail)
{

}

void drawTraylist(TrayList* list)
{

}

void drawHeader(const Mail* mail)
{

}

void showText(std::string &text)
{

}

int logMenu()
{
	return 0;
}

int mainMenu()
{
	return 0;
}

bool mailMenu()
{
	return true;
}

std::string& inputBox(std::string &message)
{
	std::string var;

	return var;//Placeholder
}

std::string& selectMail(TrayList* tray)
{
	std::string var;

	return var;//Placeholder
}

void pause()
{
	std::cin.sync();
	std::cin.get();
}