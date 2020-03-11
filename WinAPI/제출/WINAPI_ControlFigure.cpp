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

int x = 100, y = 100;
bool isRect = true;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	const RECT rt{ 100, 100, 400, 400 };
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_KEYDOWN:				//1번
		switch ((wParam))
		{
		case VK_LEFT:
			x-=10;
			break;
		case VK_RIGHT:
			x+=10;
			break;
		case VK_DOWN:
			y+=10;
			break;
		case VK_UP:
			y-=10;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	//case WM_MOUSEMOVE:			//2,3번
	//	x = LOWORD(lParam);
	//	y = HIWORD(lParam);
	//	if (x < rt.left)
	//		x = rt.left;
	//	if (x > rt.right-100)
	//		x = rt.right -100;
	//	if (y < rt.top)
	//		y = rt.top;
	//	if (y > rt.bottom-100)
	//		y = rt.bottom-100;
	//	InvalidateRect(hWnd, &rt, TRUE);
	//	return 0;
	//case WM_LBUTTONDOWN:				//3번
	//	if (MessageBox(hWnd, TEXT("도형을 바꾸시겠습니까?"), TEXT("MessageBox"), MB_YESNO) == IDYES)
	//	{
	//		if (isRect)
	//			isRect = false;
	//		else
	//			isRect = true;
	//		InvalidateRect(hWnd, NULL, TRUE);
	//	}
	//	return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, x, y, x + 100, y + 100);		//1, 2번
		//Rectangle(hdc, 100, 100, 400, 400);		//2번
		//if (isRect)								//3번
		//	Rectangle(hdc, 100, 100, 400, 400);
		//else
		//	Ellipse(hdc, 100, 100, 300, 300);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


