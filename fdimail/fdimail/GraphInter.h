#ifndef GRAPHINTER
#define GRAPHINTER
#include "TrayList.h"
#include "Mail.h"

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

	void drawMail(const Mail* mail);
	void drawTraylist(TrayList* list);
	void drawHeader(const Mail* mail);
	void showText(std::string &text);

	int logMenu();
	int mainMenu();
	bool mailMenu();
	std::string& inputBox(std::string &message);
	std::string& selectMail(TrayList* tray);

	void pause();

};
#endif //GRAPHINTER
