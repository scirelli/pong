//Good old fashoin pong

//INCLUDES////////////////
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mmsystem.h> //needed to play sound. Also have to insert winmm.lib
#include "resource.h" //needed for menu

//DEFINES ///////////////
#define RECT_LENGTH 50
#define RECT_WIDTH 4
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BALL_RADIUS 10
//defines for windows
#define WINDOW_CLASS_NAME "WINCLASS1"

//GLOBALS ///////////////
//brushes and pens
HWND main_window_handle = NULL; //save the window handle
HPEN blue_pen, white_pen, black_pen; //create pens
HBRUSH bitmap_brush; //creates a bitmap as a brush

//keys pressed
bool up_key = false;
bool down_key = false;
bool one_key = false;
bool two_key = false;
bool w_key= false;
bool s_key = false;

//FUNCTIONS ////////////
bool SinglePlayer(HDC, RECT, int, int&, int, int, int, int, int, int, int, int&);
bool FirstPlayerPaddle(HDC, RECT, int&, int&, int, int, bool, bool, int);
bool SecondPlayerPaddle(HDC, RECT, int&, int&, int, int, bool, bool, int);
void Menu(HDC, int, int);
bool DrawAndMoveBall(HDC, HINSTANCE, RECT &, HPEN, HPEN, HBRUSH, int, int , int , int &, int &, int &, int &, int &, int, int,
					 int, int, int, int, int&);
void Intro(HDC, HINSTANCE, int, int);

//\\\\\\\\\\\\\\\\\\\\\\\\\ WinProc ///////////////////////////////
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
			
			return(0); //let windows know message was handled
		}break;
	case WM_PAINT: //called when window needs repainting
		{//simply validate the window
			//ValidateRect(hwnd, NULL);
			hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			return(0); //let windows know message was handled
		}break;
	case WM_DESTROY:
		{//kill the application
			//delete the pens/brushes
			DeleteObject(blue_pen);
			DeleteObject(white_pen);
			DeleteObject(black_pen);
			DeleteObject(bitmap_brush);
			
			PostQuitMessage(0);
			return(0); //let windows know message was handled
		}break;
	
	case WM_COMMAND:
		{
			switch(wparam)
			{
			case ID_FILE_EXIT :
				{
					PostMessage(hwnd,WM_QUIT,0,0); //post a WM_QUIT message to the message queue
				}break;
			case ID_HELP_ABOUT :
				{
					MessageBox(hwnd,"The programer has created this program for \n learning purposes. If you would like the \n source code, emial:\n\t themanimal@aol.com","About",MB_OK);
				}break;
			case ID_HELP_VERSION :
				{
					MessageBox(hwnd,"Versoin 1.18","Version",MB_OK);
				}break;
			case ID_SCREENSIZE_400X400 :
				{}break;
			case ID_SCREENSIZE_640X480 :
				{}break;
			case ID_SCREENSIZE_800X600 :
				{}break;
			}//end switch on wparam
			
			return(0);// let windows know message was handled
		}//end case of WM_COMMAND

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
					case 0x31 :  //0x31=1 for some reason the variables for A-Z 0-9 dont work so have to use hex # 
						{
							one_key= true;
							break;
						}
					case 0x32 :  //0x32=2 key
						{
							two_key=true;
							break;
						}
					//Note for some reason any other key becides the arrow keys read slow so i'm going to use WM_CHAR
					//which has a higher priority then WM_KEYDOWN
					/*
					case 0x53  : //0x53=VK_S wasn't working so just used actaull value (check index for others)
						{
							s_key=true; 
						}break;
					case 0x57 : //VK_W=0x57
						{
							w_key=true;
						}break;
					*/
					default: break;

				}//end switch
			
			return(0); //let windows know message was handled
		}break; //ends WM_KEYDOWN case

	case WM_CHAR :
		{
			char ascii_code= (char)wparam;
			
			switch(ascii_code)
			{
			case 'w' :
				{
					w_key=true; 
				}break;
			case 's' :
				{
					s_key= true;
				}break;
			}//end switch
			return(0); //let windows know message was handled
		}break; //end WM_CHAR case
	
	default: 
		{
			up_key=false; 
			down_key=false;
			w_key = false;
			s_key = false;
		}break; //end main default

	}//end main switch

	//process any messages that we didn't take care of
	return(DefWindowProc(hwnd, msg, wparam, lparam));

}//end WinProc


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ WINMAIN /////////////////////////////////////////////
int WINAPI WinMain( HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow )
{
	WNDCLASS winclass; //holds the class created
	HWND hwnd;         //generic window handle
	MSG msg;           //generic message
	HDC hdc;           //generic dc
	//PAINTSTRUCT ps;    //generic paintstruct
	RECT rect;         //creates a rectangle struc
	int rect_x = 20,   //initial position of the rect (paddles)
		rect_y = 150, 
		rect2_x = WINDOW_WIDTH-25,
		rect2_y = WINDOW_HEIGHT/2,
		rect2_dy = 5; //velocity of right paddle
	int dx = 2,		  // initial velocity of ball
		dy = 4;                       
	int ball_x = WINDOW_WIDTH/2, // initial position of ball
		ball_y = WINDOW_HEIGHT/2,
		ball_y_old = 0;
	int count =0,
		delay = 10; //delay the refresh rate
	
	//fill in winclass struc
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	winclass.lpszClassName = WINDOW_CLASS_NAME;

	//register the window class
	if(!RegisterClass(&winclass))
		return(0);

	//create the window
	if(!(hwnd = CreateWindow(WINDOW_CLASS_NAME, /*class*/
							 "Cirelli's Pong", /*title*/
							 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
							 200,200, /*x,y*/
							 WINDOW_WIDTH, WINDOW_HEIGHT+20, /*width, height*/
							 NULL, /*handle to parent*/
							 NULL, /*handle to menu*/
							 hinstance, /*instance*/
							 NULL))) //creation parms
		return(0);//end if

	//save the window handle in a global
	main_window_handle = hwnd;
	
	//-----Display menu------
	hdc= GetDC(hwnd);
	//display intro
	Intro(hdc, hinstance, WINDOW_WIDTH, WINDOW_HEIGHT);
	Menu(hdc, WINDOW_WIDTH, WINDOW_HEIGHT); //Displays single/mutiplayer menu
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
		}//end if				//sends  msg to WindowProc
		
		if(one_key == true || two_key == true) //checks to see if # 1 or 2 was pressed
			break;
	}
	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	SelectObject(hdc, black_pen);
	Rectangle(hdc, 0,0,WINDOW_WIDTH,WINDOW_HEIGHT); //puts a black rectangle over menu (clears menu)
	ReleaseDC(hwnd, hdc);
	
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
		
		//\\\\\\\\\\\\\\\\\\\\   main game processing goes here /////////////////
				
		//get the graphics device context
		hdc= GetDC(hwnd);
		
		if(one_key) //single player
		{
			//------------DRAW PADDLE for first player----------------
			FirstPlayerPaddle(hdc, rect, rect_x, rect_y, RECT_WIDTH, RECT_LENGTH, up_key, down_key, WINDOW_HEIGHT);
		
			//------------DRAW BALL AND MOVE----------------
			DrawAndMoveBall(hdc, hinstance, rect, black_pen, white_pen, bitmap_brush, BALL_RADIUS, WINDOW_WIDTH, WINDOW_HEIGHT, 
							ball_x, ball_y, ball_y_old, dx, dy, RECT_LENGTH, RECT_WIDTH, rect_x, rect_y, rect2_x, rect2_y, count);
			
			/* for AI debugging "boxes"
			MoveToEx(hdc,WINDOW_WIDTH/2,0, NULL);      //center vert line
			LineTo(hdc, WINDOW_WIDTH/2,WINDOW_HEIGHT); //
			                                                                       //WINDOW_HEIGHT = y = 380
			MoveToEx(hdc, 0, WINDOW_HEIGHT/4, NULL);   //first horz line
			LineTo(hdc, WINDOW_WIDTH,WINDOW_HEIGHT/4); //                          //WINDOW_WIDTH = x = 400
			
			MoveToEx(hdc,0,WINDOW_HEIGHT/2, NULL);     //second horz line
			LineTo(hdc, WINDOW_WIDTH,WINDOW_HEIGHT/2); //
			
			MoveToEx(hdc,0,(WINDOW_HEIGHT*3)/4, NULL); //third horz line
			LineTo(hdc, WINDOW_WIDTH,(WINDOW_HEIGHT*3)/4);
			
			SetPixel(hdc, 360,350, RGB(255,255,255));
			*/
			
			//Single Player AI
			SinglePlayer(hdc, rect, rect2_x, rect2_y, RECT_WIDTH, RECT_LENGTH, ball_y_old, ball_y, ball_x, WINDOW_HEIGHT, WINDOW_WIDTH, rect2_dy);
		}
		
		if(two_key) //multiplayer
		{
			//------------DRAW PADDLE for first player and move it----------------
			FirstPlayerPaddle(hdc, rect, rect_x, rect_y, RECT_WIDTH, RECT_LENGTH, up_key, down_key, WINDOW_HEIGHT);
		
			//------------DRAW BALL AND MOVE----------------
			DrawAndMoveBall(hdc, hinstance, rect, black_pen, white_pen, bitmap_brush, BALL_RADIUS, WINDOW_WIDTH, WINDOW_HEIGHT, 
							ball_x, ball_y, ball_y_old, dx, dy, RECT_LENGTH, RECT_WIDTH, rect_x, rect_y, rect2_x, rect2_y, count);
			//------------DRAW PADDLE for second player and move it-----------
			SecondPlayerPaddle(hdc, rect, rect2_x, rect2_y, RECT_WIDTH, RECT_LENGTH, w_key, s_key, WINDOW_HEIGHT);
		}
		
		ReleaseDC(hwnd, hdc);
		
		if(count == 30) //if ball  hits cieling and floor 10 times increase speed
		{
			count =0; //reset count
			delay--;
		}
		if(delay == 2)
			delay =10; //dont want things to go to fast

		//slow things down a bit
		Sleep(delay);

	}//end while
		
	//return to Windows like this
	return(msg.wParam);
}//end WinMain
