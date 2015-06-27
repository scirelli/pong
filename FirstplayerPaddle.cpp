//Draws and moves players paddle for single player and multiplayer

#include <windows.h>
#include <windowsx.h>


bool FirstPlayerPaddle(HDC hdc, RECT rect, int& rect_x, int& rect_y, int RECT_WIDTH, int RECT_LENGTH,
					   bool up_key, bool down_key, int WINDOW_HEIGHT)
{
	//DRAW RECTANGLE----------------
	rect.left  = rect_x - RECT_WIDTH;
	rect.right = rect_x + RECT_WIDTH; 
	rect.top   = rect_y - RECT_LENGTH; 
	rect.bottom= rect_y + RECT_LENGTH; 
    
	// erase the rectangle /////////////////////////////////////
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	
	if( (up_key) && (rect_y-50 >= 0) )
		rect_y -= 5; //move rect up
	if( (down_key) && (rect_y+80 <= WINDOW_HEIGHT) )
		rect_y += 5; //move rect down

	rect.left  = rect_x - RECT_WIDTH; 
	rect.right = rect_x + RECT_WIDTH; 
	rect.top   = rect_y - RECT_LENGTH; 
	rect.bottom= rect_y + RECT_LENGTH; 
    
	// draw the rectangle /////////////////////////////////////
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	
	return true;
}