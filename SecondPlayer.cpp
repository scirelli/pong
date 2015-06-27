//Draws and moves second players paddle

#include <windows.h>
#include <windowsx.h>

bool SecondPlayerPaddle(HDC hdc, RECT rect, int& rect2_x, int& rect2_y, int RECT_WIDTH, int RECT_LENGTH,
					    bool w_key, bool s_key, int WINDOW_HEIGHT)
{
	//DRAW RECTANGLE----------------
	rect.left  = rect2_x - RECT_WIDTH;
	rect.right = rect2_x + RECT_WIDTH; 
	rect.top   = rect2_y - RECT_LENGTH; 
	rect.bottom= rect2_y + RECT_LENGTH; 
    
	// erase the rectangle /////////////////////////////////////
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	
	if( (w_key) && (rect2_y-50 >= 0) ) //if hit w key move paddle up
		rect2_y -= 5; //move rect up
	if( (s_key) && (rect2_y+80 <= WINDOW_HEIGHT) ) //if hit s key move paddle down
		rect2_y += 5; //move rect down

	rect.left  = rect2_x - RECT_WIDTH; 
	rect.right = rect2_x + RECT_WIDTH; 
	rect.top   = rect2_y - RECT_LENGTH; 
	rect.bottom= rect2_y + RECT_LENGTH; 
    
	// draw the rectangle /////////////////////////////////////
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	
	return true;
}