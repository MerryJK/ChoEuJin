#pragma once
#include"CardManager.h"

class GameManager
{
private:
	CardManager CM;
	int m_iCurCardType;
	int m_iPreCardType;
public:
	GameManager();
	void InIt(HWND, HINSTANCE);
	void DrawGame(HDC);
	void PlayGame(HWND, POINT);
	void CloseCards(HWND);
	~GameManager();
};

