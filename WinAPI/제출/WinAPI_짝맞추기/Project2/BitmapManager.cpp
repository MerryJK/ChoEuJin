#include "BitmapManager.h"

BitmapManager* BitmapManager::m_pThis = NULL;

BitmapManager::BitmapManager()
{
	m_bt = new Bitmap[CARD_END];
	m_backBt = new Bitmap;
}

void BitmapManager::Init(HWND hWnd, HINSTANCE hInst)
{
	int id = CARD_DOG;
	HDC hdc = GetDC(hWnd);
	for (int i = 0; i < CARD_END; i++)
	{
		m_bt[i].InIt(hdc, hInst, id);
		id++;
	}
	m_backBt->InIt(hdc, hInst, CARD_BACK);
	ReleaseDC(hWnd, hdc);
}

void BitmapManager::Draw(HDC hdc, int x, int y)
{
	m_bt->Draw(hdc, x, y);
}

void BitmapManager::Release()
{
	delete(m_pThis);
}

BitmapManager::~BitmapManager()
{
	delete(m_bt);
	delete(m_backBt);
}
