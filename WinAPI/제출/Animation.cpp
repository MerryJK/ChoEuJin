#include <Windows.h>
#include <time.h>

enum STATE
{
	STATE_NONE = -1,
	STATE_DOWN,
	STATE_UP,
	STATE_LEFT,
	STATE_RIGHT,
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Animal Card");
static COLORREF redColor = RGB(255, 0, 0);
int changeX = 0, changeY = 0;
int curTime, prevTime = clock();
float deltaTime = 0.0f;
STATE state = STATE_NONE;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	curTime = clock();
	srand((unsigned)time(NULL));
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

void KeepMoving(STATE curstate, STATE changestate)
{
	if (curstate == changestate)
	{
		if (changeX > 2)
			changeX = 0;
		else
			changeX++;
	}
	else
		changeX = 0;
	changeY = changestate;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HDC hMemDC;
	HBITMAP hImage, hOldBitmap;
	PAINTSTRUCT ps;
	BITMAP bit;
	POINT pt;
	int bx, by;
	deltaTime++;

	switch (iMessage) {
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			KeepMoving(state, STATE_RIGHT);
			state = STATE_RIGHT;
			break;
		case VK_LEFT:
			KeepMoving(state, STATE_LEFT);
			state = STATE_LEFT;
			break;
		case VK_UP:
			KeepMoving(state, STATE_UP);
			state = STATE_UP;
			break;
		case VK_DOWN:
			KeepMoving(state, STATE_DOWN);
			state = STATE_DOWN;
			break;
		}
		//if (curTime - prevTime > 500)
		//{
		//	InvalidateRect(hWnd, NULL, true);
		//	prevTime = curTime;
		//}
		if (deltaTime >= 5)
		{
			InvalidateRect(hWnd, NULL, true);
			deltaTime = 0.0f;
		}
		return 0;
	case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			hMemDC = CreateCompatibleDC(hdc);
			hImage = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);
			GetObject(hImage, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;

			TransparentBlt(hdc, 650, 50, bx / 4, by / 4, hMemDC, (bx / 4) * changeX, (by / 4) * changeY, bx / 4, by / 4, RGB(255, 0, 255));

			SelectObject(hMemDC, hOldBitmap);
			DeleteObject(hImage);
			DeleteDC(hMemDC);
			EndPaint(hWnd, &ps);
			return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void bla()
{

}