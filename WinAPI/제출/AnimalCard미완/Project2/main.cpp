#include"CardManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Animal Card");
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HDC hdc, MemDC; 
	//PAINTSTRUCT ps;
	//HBITMAP myBitmap, oldBitmap;
	int x =-1, y=-1;
	switch (iMessage) {
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		CardManager::GetInstance()->CheckClickedCards(hWnd, x, y);
		return 0;
	case WM_PAINT: 
		//hdc = BeginPaint(hWnd, &ps);
		CardManager::GetInstance()->SetCards();
		CardManager::GetInstance()->DrawCards(hWnd, g_hInst);
		//MemDC = CreateCompatibleDC(hdc);
		//myBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		//oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap); 
		//BitBlt(hdc, 100, 100, 145, 235, MemDC, 0, 0, SRCCOPY);
		//StretchBlt(hdc, 300, 100, 290, 470, MemDC, 0, 0, 145, 235, SRCCOPY);
		//SelectObject(MemDC, oldBitmap);
		//DeleteObject(myBitmap);
		//DeleteDC(MemDC);
	//EndPaint(hWnd, &ps); 
	return 0; 
	case WM_DESTROY:  
		PostQuitMessage(0); 
		return 0;
	} 
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}