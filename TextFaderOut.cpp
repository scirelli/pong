//TextFaderOut fades a string to black

#include <windows.h>
#include <windowsx.h>
#include <string.h>

void TextFaderOut(HDC hdc, int x, int y, char * string)
{
	int i=0;
	
	SetBkMode(hdc, TRANSPARENT);
	
	//fade to black
	while(i<=255)
	{
		SetTextColor(hdc, RGB(255-i,255-i,255-i));
		TextOut(hdc, x, y, string, strlen(string));
		Sleep(10);
		i++;
	}
	
	return;
}