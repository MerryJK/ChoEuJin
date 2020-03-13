#include<Windows.h>
#include<algorithm>
#include<time.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimeProc(HWND, UINT, UINT, DWORD);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Hello Wolrd");
static COLORREF redColor = RGB(255, 0, 0);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

int x = 100; int y = 100;
int radius = 50; int xCenter = 200; int yCenter = 200;
int S, M, H;
int sX = 0; int sY = 0; int sAngle;
int mX = 0; int mY = 0; int mAngle;
int hX = 0; int hY = 0; int hAngle;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	const RECT rt{ 100, 100, 400, 400 };
	SYSTEMTIME st;
	GetLocalTime(&st);
	S = st.wSecond;
	M = st.wMinute;
	H = st.wHour;
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, TimeProc);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, 100, 100, 300, 300);
		MoveToEx(hdc, xCenter, yCenter, NULL);
		LineTo(hdc, sX, sY);
		MoveToEx(hdc, xCenter, yCenter, NULL);
		LineTo(hdc, mX, mY);
		MoveToEx(hdc, xCenter, yCenter, NULL);
		LineTo(hdc, hX, hY);
		//Rectangle(hdc, 100, 100, 400, 400);
		//Ellipse(hdc, x, y, x + 50, y + 50);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//bool isRight = true;
//bool isDown = true;
//void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) 
//{
//	if (x > rt.right - 50)
//		isRight = false;
//	else if (x < rt.left)
//		isRight = true;
//
//	if (y > rt.bottom - 51)
//		isDown = false;
//	else if (y < rt.top)
//		isDown = true;
//
//	if (isRight)
//		x++;
//	else
//		x--;
//	if (isDown)
//		y++;
//	else
//		y--;
//	InvalidateRect(hWnd, NULL, TRUE); 
//}

void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	sAngle = S * (360 / 60)+270;
	mAngle = M * (360 / 60)+270;
	hAngle = H * (360 / 12)+270;
	sX = xCenter + (cos(sAngle) * radius)*1.2;
	sY = yCenter + (-sin(sAngle) * radius)*1.2;
	mX = xCenter + (cos(mAngle) * radius)*1.4;
	mY = yCenter + (-sin(mAngle) * radius)*1.4;
	hX = xCenter + (cos(hAngle) * radius);
	hY = yCenter + (-sin(hAngle) * radius);
	//sAngle++;
	//if (sAngle % 12 == 0)
	//	mAngle++;
	//if (mAngle % 12 == 0)
	//	hAngle++;
	//if (sAngle == 360)
	//	sAngle = 0;
	//if (mAngle == 360)
	//	mAngle = 0;
	//if (hAngle == 360)
	//	hAngle = 0;
	InvalidateRect(hWnd, NULL, TRUE);
}