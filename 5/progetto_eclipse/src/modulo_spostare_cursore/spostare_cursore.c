#include "spostare_cursore.h"


#include <windows.h>


void spostare_cursore(int x, int y) {
	COORD CursorPos = {x, y};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, CursorPos);
	return;
}
