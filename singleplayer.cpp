#include <windows.h>
#include <windowsx.h>

bool SinglePlayer(HDC hdc, RECT rect, int rect2_x, int& rect2_y, int RECT_WIDTH, int RECT_LENGTH, int ball_y_old, 
				  int ball_y, int ball_x, int WINDOW_HEIGHT, int WINDOW_WIDTH, int& rect2_dy)
{
	bool stop= false;

	//DRAW SINGLE PLAYER (CPU) PADDLE------And AI----------
	rect.left  = rect2_x - RECT_WIDTH;
	rect.right = rect2_x + RECT_WIDTH; 
	rect.top   = rect2_y - RECT_LENGTH; //ball_y_old
	rect.bottom= rect2_y + RECT_LENGTH; 
	
	//erase rect2
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	
	if(rect2_y+RECT_LENGTH >= WINDOW_HEIGHT-15) //if paddle hits floor reverse direction
	{
		stop= true;
		rect2_y--;
	}
	if(rect2_y-RECT_LENGTH <= 0 )  //if paddle hits ceiling reverse direction
	{
		stop= true;
		rect2_y++;
	}
	if(ball_x >= WINDOW_WIDTH-15)  //if ball goes past paddle stop moving
		stop = true;
	if( ball_x >= WINDOW_WIDTH/2 && ball_y <= WINDOW_HEIGHT/4 && stop == false) //if ball is with in first box
	{ //move paddle
		rect2_y -= rect2_dy;
	}
	if( ball_x >= WINDOW_WIDTH/2 && ball_y >= (WINDOW_HEIGHT*3)/4 && stop == false) //if ball is with in last box
		rect2_y += rect2_dy;
	if( (ball_x >= WINDOW_WIDTH/2 && stop == false) && (ball_y >= WINDOW_HEIGHT/4 && ball_y <= WINDOW_HEIGHT/2) ) //if ball is in second box
	{
		if(ball_y < rect2_y)
			rect2_y -= rect2_dy;
		if(ball_y > rect2_y)
			rect2_y += rect2_dy;
	}
	if( (ball_x >= WINDOW_WIDTH/2 && stop == false) && (ball_y <= (WINDOW_HEIGHT*3)/4 && ball_y >= WINDOW_HEIGHT/2 ) )
	{
		if(ball_y < rect2_y)
			rect2_y -= rect2_dy;
		if(ball_y > rect2_y)
			rect2_y += rect2_dy;
	}
		
	rect.left  = rect2_x - RECT_WIDTH;
	rect.right = rect2_x + RECT_WIDTH; 
	rect.top   = rect2_y - RECT_LENGTH; 
	rect.bottom= rect2_y + RECT_LENGTH; 
		
	//Draw rect2
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	
	
	return true;
}