#include "utilsWin.h"
#include <windows.h>

void fontConsole()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.FontWeight = 400;
	cfi.nFont = 1;
	cfi.dwFontSize.X = 12; cfi.dwFontSize.Y = 20;
	cfi.FontFamily = 54;
	wcscpy_s(cfi.FaceName, L"LucidaConsole");
	SetCurrentConsoleFontEx(hStdOut, false, &cfi);
}

void backgroundTextAtt(int color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15 | (color << 4));
}

int getKey()
{
	int key; DWORD cNumRead; INPUT_RECORD irInBuf;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	do{
		do{
			ReadConsoleInput(hStdIn, &irInBuf, 1, &cNumRead);
		} while (irInBuf.EventType != KEY_EVENT);
		if (irInBuf.Event.KeyEvent.uChar.AsciiChar == 0){
			ReadConsoleInput(hStdIn, &irInBuf, 1, &cNumRead);
			key = irInBuf.Event.KeyEvent.wVirtualKeyCode;
		}
		else key = irInBuf.Event.KeyEvent.uChar.AsciiChar;
	} while (key != VK_ESCAPE && key != VK_LEFT && key != VK_UP
		&& key != VK_RIGHT  && key != VK_DOWN);
	//loop until game key is pressed
	return key;
}
