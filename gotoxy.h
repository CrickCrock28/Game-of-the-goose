#ifndef GOTOXY_H_
#define GOTOXY_H_

#include <windows.h>

void GotoXY(int x, int y) {
	COORD CursorPos = {x, y};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, CursorPos);
}

#endif /* GOTOXY_H_ */
