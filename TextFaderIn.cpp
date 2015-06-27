//TextFaderOut fades a string from black to white

#include <windows.h>
#include <windowsx.h>
#include <string.h>

void TextFaderIn(HDC hdc, int x, int y, char * string)
{
	int i=255;
	
	SetBkMode(hdc, TRANSPARENT);
	
	//fade to white
	while(i>=0)
	{
		SetTextColor(hdc, RGB(255-i,255-i,255-i));
		TextOut(hdc, x,y, string, strlen(string));
		Sleep(10);
		i--;
	}
	
	return;
}