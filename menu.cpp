#include <windows.h>
#include <windowsx.h>

void Menu(HDC hdc, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255,255,255));
	TextOut(hdc, (WINDOW_WIDTH/4)+100, (WINDOW_HEIGHT/2)-50,"Select an Option:", 17);
	TextOut(hdc, (WINDOW_WIDTH/4)+75, (WINDOW_HEIGHT/2)-30, "Press 1 for single player", 25); 
	TextOut(hdc, (WINDOW_WIDTH/4)+75,(WINDOW_HEIGHT/2)-10, "Press 2 for multiplayer", 23); 
	
	return;
}