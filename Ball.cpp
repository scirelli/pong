//draws and moves ball
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

bool DrawAndMoveBall(HDC hdc, HINSTANCE hinstance, RECT &rect, HPEN black_pen, HPEN white_pen, HBRUSH bitmap_brush, 
					 int BALL_RADIUS, int WINDOW_WIDTH, int WINDOW_HEIGHT, int & ball_x, int & ball_y, int& ball_y_old, 
					 int& dx, int& dy, int RECT_LENGTH, int RECT_WIDTH, int rect_x, int rect_y, int rect2_x, 
					 int rect2_y, int& count)
{
	//fill in ballrect struc
	rect.left = ball_x - BALL_RADIUS;
	rect.right = ball_x + BALL_RADIUS;
	rect.top = ball_y - BALL_RADIUS;
	rect.bottom = ball_y + BALL_RADIUS;
		
	//erase the ball
	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	//SelectObject(hdc, bitmap_brush);
	SelectObject(hdc, black_pen);
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
		
	// move the ball //////////////////////////////////////
	ball_y_old= ball_y;
	ball_x+=dx; //dx=4 ball_x=204
	ball_y+=dy;	//dy=2 ball_y=202
		
	if ( ( ball_x-BALL_RADIUS <= rect_x && ball_x-BALL_RADIUS >= rect_x-RECT_WIDTH ) && 
		 ( ball_y >= rect_y-RECT_LENGTH && ball_y <= rect_y+RECT_LENGTH ) )//if ball hits left paddle
	{
		// reverse x velocity
		dx=-dx;
		// move ball back
		ball_x+=dx;
		PlaySound(MAKEINTRESOURCE(IDR_WAVE3), hinstance, SND_RESOURCE | SND_ASYNC);
	} // end if

	if ( ( ball_x+BALL_RADIUS >= rect2_x-RECT_WIDTH && ball_x+BALL_RADIUS <= rect2_x ) && 
		 ( ball_y >= rect2_y-RECT_LENGTH && ball_y <= rect2_y+RECT_LENGTH ) )//if ball hits right paddle
	{                    
		// reverse x velocity
		dx=-dx;
		// move ball back
		ball_x+=dx;
		PlaySound(MAKEINTRESOURCE(IDR_WAVE3), hinstance, SND_RESOURCE | SND_ASYNC);
	} // end if
	
	if (ball_y+BALL_RADIUS >= WINDOW_HEIGHT-15 || ball_y-BALL_RADIUS <=0) //if ball hits cieling or floor
	{
		// reverse y velocity
		dy=-dy;
		// move ball back
		ball_y+=dy;
		count++; //counts how many times ball hits cieling/floor
		PlaySound(MAKEINTRESOURCE(IDR_WAVE2), hinstance, SND_RESOURCE | SND_ASYNC);
	} // end if
	
	if(ball_x >= WINDOW_WIDTH) //if ball hits right wall
	{
		ball_x=WINDOW_WIDTH/2;
		ball_y=WINDOW_HEIGHT/2;
		dx=-dx;
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), hinstance, SND_RESOURCE | SND_SYNC);
		//Sleep(500); //delay to give players a chance to reset
	}

	if( ball_x <=0 ) //if ball hits left wall
	{
		ball_x=WINDOW_WIDTH/2;
		ball_y=WINDOW_HEIGHT/2;
		dx=-dx;
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), hinstance, SND_RESOURCE | SND_SYNC);
		//Sleep(500);
	}
		
	// fill in rect structure with new position
	rect.left  = ball_x - BALL_RADIUS;
	rect.right = ball_x + BALL_RADIUS;
	rect.top   = ball_y - BALL_RADIUS;
	rect.bottom= ball_y + BALL_RADIUS;
    
	//draw the ball
	SelectObject(hdc, white_pen);
	SelectObject(hdc,GetStockObject(WHITE_BRUSH));
	//SelectObject(hdc, bitmap_brush);
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
		
	return true;
}