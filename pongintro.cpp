#include <windows.h>
#include <windowsx.h>
#include "resource.h"

void TextFaderOut(HDC, int, int, char *);
void TextFaderIn(HDC, int, int, char *);

void Intro(HDC hdc, HINSTANCE hinstance, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	int i=0;
	
	PlaySound(MAKEINTRESOURCE(IDR_WAVE4), hinstance, SND_RESOURCE | SND_ASYNC);
	Sleep(7355);
	//fade to black
	TextFaderIn(hdc, (WINDOW_WIDTH/4)+100, (WINDOW_HEIGHT/2)-50, "In the begining");
	TextFaderOut(hdc, (WINDOW_WIDTH/4)+100, (WINDOW_HEIGHT/2)-50, "In the begining");
	
	TextFaderIn(hdc, (WINDOW_WIDTH/4)+100, (WINDOW_HEIGHT/2)-50, "There was pong");
	TextFaderOut(hdc, (WINDOW_WIDTH/4)+100, (WINDOW_HEIGHT/2)-50, "There was pong");
	
	TextFaderIn(hdc, (WINDOW_WIDTH/4)+100, (WINDOW_HEIGHT/2)-50, "And today...");
	TextFaderOut(hdc, (WINDOW_WIDTH/4)+100, (WINDOW_HEIGHT/2)-50, "And today...");

	TextFaderIn(hdc, (WINDOW_WIDTH/4)+100, (WINDOW_HEIGHT/2)-50, "There is still pong");
	
	//over right last string in black
	SetTextColor(hdc, RGB(0,0,0));
	TextOut(hdc, (WINDOW_WIDTH/4)+100, (WINDOW_HEIGHT/2)-50, "There is still pong",20);
	
	//let it sink in
	Sleep(200);

	return;
}