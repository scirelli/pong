#include <windows.h>
#include <windowsx.h>

bool SinglePlayer(HDC hdc, RECT rect, int rect2_x, int& rect2_y, int RECT_WIDTH, 
				  int RECT_LENGTH, int ball_y_old, int ball_y, int WINDOW_HEIGHT, int change_y_by)
{
	//int rect2_dy=1;

	rect2_y = ball_y; //current y positon of rect2
	
	if( (rect2_y + RECT_LENGTH <= WINDOW_HEIGHT) && (rect2_y - RECT_LENGTH >= 0) )
	{
		//DRAW SINGLE PLAYER PADDLE----------------
		
		rect.left  = rect2_x - RECT_WIDTH;
		rect.right = rect2_x + RECT_WIDTH; 
		rect.top   = ball_y_old - RECT_LENGTH; //ball_y_old
		rect.bottom= ball_y_old + RECT_LENGTH; 
	
		//erase rect2
		FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	
		//move rect2
		//rect2_y += rect2_dy;

		rect.left  = rect2_x - RECT_WIDTH;
		rect.right = rect2_x + RECT_WIDTH; 
		rect.top   = rect2_y - RECT_LENGTH; 
		rect.bottom= rect2_y + RECT_LENGTH; 
		
		//Draw rect2
		FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	}
	
	return true;
}