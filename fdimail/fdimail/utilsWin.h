#ifndef UTILSWIN
#define UTILSWIN

#include <Windows.h>

enum keys { UP = VK_UP, RIGHT = VK_RIGHT, LEFT = VK_LEFT, DOWN = VK_DOWN, ESCAPE = VK_ESCAPE, ENTER = VK_RETURN };

int getKey()
{
	int key; DWORD cNumRead; INPUT_RECORD irInBuf;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	
	do
	{
		FlushConsoleInputBuffer(hStdIn);
		do
		{
			ReadConsoleInput(hStdIn, &irInBuf, 1, &cNumRead);
		} while (irInBuf.EventType != KEY_EVENT || irInBuf.Event.KeyEvent.bKeyDown);
		if (irInBuf.Event.KeyEvent.uChar.AsciiChar == 0)
		{
			
			key = irInBuf.Event.KeyEvent.wVirtualKeyCode;
		}
		else key = irInBuf.Event.KeyEvent.uChar.AsciiChar;
	} while (key != VK_ESCAPE && key != VK_LEFT && key != VK_UP && key != VK_ESCAPE
		&& key != VK_RIGHT  && key != VK_DOWN && key != VK_RETURN);
	//loop until key is pressed
	return key;
}

#endif