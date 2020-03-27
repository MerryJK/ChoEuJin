#pragma once
#include "define.h"

class Bitmap
{
private:
	HDC memDC;
	HBITMAP m_pBitmap;
	HBITMAP m_pBitOld;
	SIZE m_size;
public:
	inline SIZE GetSize() { return m_size; }
	void InIt(HDC hdc, HINSTANCE hInst, int id);
	void Draw(HDC hdc, int x, int y, float cpX = 0.5f, float cpY = 0.5f);
	Bitmap();
	~Bitmap();
};

