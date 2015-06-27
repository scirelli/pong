//Good old fashoin pong

//INCLUDES////////////////
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//DEFINES ///////////////
#define RECT_LENGTH 50
#define RECT_WIDTH 5
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define BALL_RADIUS 10

//defines for windows
#define WINDOW_CLASS_NAME "WINCLASS1"

//GLOBALS ///////////////
HWND main_window_handle = NULL; //save the window handle
HPEN blue_pen, white_pen, black_pen; //create pens
HBRUSH blue_brush; //creates a brush
bool up_key = false;
bool down_key = false;

//FUNCTIONS ////////////
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//main message handler of the system
	PAINTSTRUCT ps; // used in WM_PAINT
	HDC hdc;        // handle to the device context

	//find out what the message is
	switch(msg)
	{
	case WM_CREATE: //called when window is created
		{ //do initialization here
			white_pen = CreatePen(PS_SOLID,0,RGB(255,255,255)); //create white_pen
			blue_pen = CreatePen(PS_SOLID,0,RGB(0,0,255));      //create blue_pen
			black_pen = CreatePen(PS_SOLID,0,RGB(0,0,0));
			blue_brush= CreateSolidBrush(RGB(0,0,255));
			return(0);
		}break;
	case WM_PAINT: //called when window needs repainting
		{//simply validate the window
			//ValidateRect(hwnd, NULL);
			hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			return(0);
		}break;
	case WM_DESTROY:
		{//kill the application
			//delete the pens
			DeleteObject(blue_pen);
			DeleteObject(white_pen);
			DeleteObject(black_pen);
			DeleteObject(blue_brush);
			PostQuitMessage(0);
			return(0);
		}break;
	case WM_KEYDOWN:
		{
			int virtual_code= (int)wparam;
			int key_bits= (int)lparam;
			
			switch(virtual_code)
				{
					case VK_LEFT :
						{
							break; //left arrow
						}
					case VK_RIGHT : 
						{
							break; //right arrow
						}
					case VK_UP : 
						{
							up_key=true;
							break; //up arrow
						}
					case VK_DOWN : 
						{
							down_key = true;
							break; //down arrow
						}
					default: break;

				}//end switch
			
			return(0);
		}break;
	default: 
		{
			up_key=false; 
			down_key=false; 
		}break;

	}//end switch

	//process any messages that we didn't take care of
	return(DefWindowProc(hwnd, msg, wparam, lparam));

}//end WinProc

//WINMAIN /////////////////////////////////////////////
int WINAPI WinMain( HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{
	WNDCLASS winclass; //holds the class created
	HWND hwnd;         //generic window handle
	MSG msg;           //generic message
	HDC hdc;           //generic dc
	PAINTSTRUCT ps;    //generic paintstruct
	RECT rect;         //creates a rectangle struc
	int rect_x = 20;   //initial position of the rect
	int rect_y = 150; 
	int dx = 2, dy = 4;        // initial velocity of ball               
	int ball_x = WINDOW_WIDTH/2, // initial position of ball
		ball_y = WINDOW_WIDTH/2,
		ball_y_old = 0;
	int rect2_x = 370,
		rect2_y = ball_y;

	//fill in winclass struc
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;

	//register the window class
	if(!RegisterClass(&winclass))
		return(0);

	//create the window
	if(!(hwnd = CreateWindow(WINDOW_CLASS_NAME, /*class*/
							 "Cirelli's Pong", /*title*/
							 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
							 0,0, /*x,y*/
							 400, 400, /*width, height*/
							 NULL, /*handle to parent*/
							 NULL, /*handle to menu*/
							 hinstance, /*instance*/
							 NULL))) //creation parms
		return(0);

	//save the window handle in a global
	main_window_handle = hwnd;
	
	//enter main event loop
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0,0,PM_REMOVE))
		{
			//test if this is a quit message
			if(msg.message == WM_QUIT)
				break;
			
			//translate any accelorator keys
			TranslateMessage(&msg);

			//send the message to the window proc
			DispatchMessage(&msg);
		}//end if
		
		//main game processing goes here /////////////////
				
		//get the graphics device context
		hdc= GetDC(hwnd);
		
		//DRAW RECTANGLE----------------
		rect.left  = rect_x - RECT_WIDTH;
		rect.right = rect_x + RECT_WIDTH; 
		rect.top   = rect_y - RECT_LENGTH; 
		rect.bottom= rect_y + RECT_LENGTH; 
    
		// erase the rectangle /////////////////////////////////////
		FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		
		if( (up_key) && (rect_y-50 >= 0) )
			rect_y -= 5; //move rect up
		if( (down_key) && (rect_y+80 <= 400) )
			rect_y += 5; //move rect down

		rect.left  = rect_x - RECT_WIDTH; 
		rect.right = rect_x + RECT_WIDTH; 
		rect.top   = rect_y - RECT_LENGTH; 
		rect.bottom= rect_y + RECT_LENGTH; 
    
		// draw the rectangle /////////////////////////////////////
		FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		
		//DRAW BALL ----------------

		//fill in ballrect struc
		rect.left = ball_x - BALL_RADIUS;
		rect.right = ball_x + BALL_RADIUS;
		rect.top = ball_y - BALL_RADIUS;
		rect.bottom = ball_y + BALL_RADIUS;
		
		//erase the ball
		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		SelectObject(hdc, black_pen);
		Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
		
		// move the ball //////////////////////////////////////
		ball_y_old= ball_y;
		ball_x+=dx; //dx=4 ball_x=204
		ball_y+=dy;	//dy=2 ball_y=202
		
		if (ball_x >= WINDOW_WIDTH || ( (ball_x-BALL_RADIUS == rect_x)&&(ball_y >= rect_y-RECT_LENGTH)&&(ball_y <= rect_y+RECT_LENGTH) ) )
		{
			// reverse x velocity
			dx=-dx;

			// move ball back
			ball_x+=dx;
		} // end if
    
		if (ball_y >= WINDOW_HEIGHT || ball_y <=0)
		{
			// reverse y velocity
			dy=-dy;

			// move ball back
			ball_y+=dy;
		} // end if

		if( ball_x <=0 )
		{
			ball_x=200;
			ball_y=200;
			dx=-dx;
			Sleep(1000);
		}

		// fill in rect structure with new position
		rect.left  = ball_x - BALL_RADIUS;
		rect.right = ball_x + BALL_RADIUS;
		rect.top   = ball_y - BALL_RADIUS;
		rect.bottom= ball_y + BALL_RADIUS;
    
		// draw the ball
		SelectObject(hdc, white_pen);
		SelectObject(hdc,GetStockObject(WHITE_BRUSH));
		//SelectObject(hdc, blue_brush);
		Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
    
		//DRAW SECOND PLAYER PADDLE----------------

		rect.left  = rect2_x - RECT_WIDTH;
		rect.right = rect2_x + RECT_WIDTH; 
		rect.top   = ball_y_old - RECT_LENGTH; 
		rect.bottom= ball_y_old + RECT_LENGTH; 
		
		//erase rect2
		FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		
		//move rect2
				
		rect.left  = rect2_x - RECT_WIDTH;
		rect.right = rect2_x + RECT_WIDTH; 
		rect.top   = ball_y - RECT_LENGTH; 
		rect.bottom= ball_y + RECT_LENGTH; 
		
		//Draw rect2
		FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		
		
		ReleaseDC(hwnd, hdc);
		
		//slow things down a bit
		Sleep(10);
	}//end while
	//return to Windows like this
	return(msg.wParam);
}//end WinMain
