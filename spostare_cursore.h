#ifndef SPOSTARE_CURSORE_H_
#define SPOSTARE_CURSORE_H_

#include <windows.h>

void spostare_cursore(int x, int y) {
	COORD CursorPos = {x, y};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, CursorPos);
}

#endif /* SPOSTARE_CURSORE_H_ */
