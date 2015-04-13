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

void GraphInter::drawMail(const Mail* mail)
{

}

void GraphInter::drawTraylist(TrayList* list)
{

}

void GraphInter::drawHeader(const Mail* mail)
{

}

void GraphInter::showText(std::string &text)
{

}

int GraphInter::logMenu()
{
	return 0;//Placeholder
}

int GraphInter::mainMenu()
{
	return 0;//Placeholder
}

bool GraphInter::mailMenu()
{
	return false;//Placeholder
}

std::string& GraphInter::inputBox(std::string &message)
{
	return message;//Placeholder
}

std::string& GraphInter::selectMail(TrayList* tray)
{
	std::string var;

	return var;//Placeholder
}

void GraphInter::pause()
{
	std::cin.sync();
	std::cin.get();
}