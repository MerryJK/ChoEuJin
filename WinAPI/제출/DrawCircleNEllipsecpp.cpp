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

void SetCircle(HDC hdc, int xCenter, int yCenter, int radius)
{
	int x = 0;
	int y = radius;

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
	const char *str = TEXT("asdf");
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		int x = 0, y = 0;
		SetCircle(hdc, 200, 200, 100);
		SetEllips(hdc, 500, 200, 100, 50);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}