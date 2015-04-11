#ifndef GRAPHINTER
#define GRAPHINTER
#include "TrayList.h"
#include "Mail.h"

//Graphical Interface. May be used to implement SFML, as of now prints through the console
class GraphInter
{
public:
	GraphInter();
	~GraphInter();

	void drawMail(const Mail* mail);
	void drawTraylist(TrayList* list);
	void drawHeader(const Mail* mail);
	void showText(std::string &text);

	std::string& inputBox(std::string &message);

};
#endif //GRAPHINTER
