#pragma once
#include "Bitmap.h"

class BitmapManager
{
	static BitmapManager *m_pThis;
	Bitmap* m_bt;
	Bitmap* m_backBt;
public:
	BitmapManager();
	static BitmapManager* GetInstance()
	{
		if (m_pThis == NULL)
			m_pThis = new BitmapManager;
		return m_pThis;
	}
	inline Bitmap* GetImage(CARD_TYPE image)
	{
		int index = image - 101;
		return &m_bt[index];
	}
	inline Bitmap* GetBackCard()
	{
		return m_backBt;
	}
	void Init(HWND hWnd, HINSTANCE hInst);
	void Draw(HDC hdc, int x, int y);
	void Release();
	~BitmapManager();
};

