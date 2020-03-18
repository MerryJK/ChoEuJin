#include<Windows.h>
#include<algorithm>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
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

void DrawCircle(HDC hdc, int xCenter, int yCenter, int x, int y)
{
	SetPixel(hdc, xCenter + x, yCenter + y, redColor);
	SetPixel(hdc, xCenter + x, yCenter - y, redColor);
	SetPixel(hdc, xCenter - x, yCenter + y, redColor);
	SetPixel(hdc, xCenter - x, yCenter - y, redColor);
	SetPixel(hdc, xCenter + y, yCenter + x, redColor);
	SetPixel(hdc, xCenter + y, yCenter - x, redColor);
	SetPixel(hdc, xCenter - y, yCenter + x, redColor);
	SetPixel(hdc, xCenter - y, yCenter - x, redColor);
}

void SetCircle(HDC hdc, int xCenter, int yCenter, int radius)
{
	int x = 0;
	int y = radius;
	
	//int p = 1 - radius;
	//DrawCircle(hdc, xCenter, yCenter, x, y);
	//while (x < y) {
	//	x++;
	//	if (p < 0) {
	//		p += 2 * x + 1;
	//	}
	//	else {
	//		y--;
	//		p += 2 * (x - y) + 1;
	//	}
	//	DrawCircle(hdc, xCenter, yCenter, x, y);
	//}
	for (int angle = 0; angle <= 360; angle++)
	{
		int x = (cos(angle) * radius);
		int y = (sin(angle) * radius);
		SetPixel(hdc, xCenter + x, yCenter + y, redColor);
	}

}

void SetEllips(HDC hdc, int xCenter, int yCenter, int xRadius, int yRadius)
{
	int x = 0;
	int y = yRadius;
	
	for (int angle = 0; angle <= 360; angle++)
	{
		int x = (cos(angle) * xRadius);
		int y = (sin(angle) * yRadius);
		SetPixel(hdc, xCenter + x, yCenter + y, redColor);
	}

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	RECT rt = { 100, 100, 400, 300 };
	const char *str =  TEXT("asdf");
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	//case WM_LBUTTONDOWN:
	//	hdc = GetDC(hWnd);
	//	TextOut(hdc, 100, 100, TEXT("BEAUTIFUL"), 10);
	//	ReleaseDC(hWnd, hdc);
	//	return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		int x = 0, y = 0;
		SetCircle(hdc, 200, 200, 100);
		SetEllips(hdc, 500, 200, 100, 50);
		//MoveToEx(hdc, 50, 50, NULL);
		//LineTo(hdc, 300, 90);
		//Rectangle(hdc, 50, 100, 200, 180);
		//Ellipse(hdc, 220, 100, 400, 200);
		//DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}