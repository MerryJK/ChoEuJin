#include "Bitmap.h"

Bitmap::Bitmap()
{
}

void Bitmap::InIt(HDC hdc, HINSTANCE hIns, int id)
{
	memDC = CreateCompatibleDC(hdc);
	m_pBitmap = (HBITMAP)LoadBitmap(hIns, MAKEINTRESOURCE(id));
	m_pBitOld = (HBITMAP)SelectObject(memDC, m_pBitmap);
	BITMAP Bitmap_info;
	GetObject(m_pBitmap, sizeof(Bitmap_info), &Bitmap_info);
	m_size.cx = Bitmap_info.bmWidth;
	m_size.cy = Bitmap_info.bmHeight;
}

void Bitmap::Draw(HDC hdc, int x, int y, float cpX, float cpY)
{
	StretchBlt(hdc, x, y, m_size.cx * cpX, m_size.cy * cpY, memDC, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
}

Bitmap::~Bitmap()
{
	SelectObject(memDC, m_pBitOld);
	DeleteObject(m_pBitmap);
	DeleteDC(memDC);
}
