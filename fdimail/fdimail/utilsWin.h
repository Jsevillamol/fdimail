#ifndef UTILSWIN
#define UTILSWIN
inline void cpConsoleOut(int cp);
void fontConsole();
void backgroundTextAtt(int color);
int getKey();

#include <Windows.h>

enum keys { UP = VK_UP, RIGHT = VK_RIGHT, LEFT = VK_LEFT, DOWN = VK_DOWN, ESCAPE = VK_ESCAPE };

inline void cpConsoleOut(int cp)
{
	SetConsoleOutputCP(cp);
}

#endif