#pragma once
#include "AnimalCard.h"
#include <vector>

class CardManager
{
private:
	HDC hdc, memDC;
	PAINTSTRUCT ps;
	static CardManager *CM;
	std::vector<AnimalCard*> m_vCardList;
public:
	static CardManager* GetInstance()
	{
		if (CM == NULL)
			CM = new CardManager;
		return CM;
	}
	void SetCards();
	void DrawCards(HWND, HINSTANCE);
	void CheckClickedCards(HWND, int, int);
	CardManager();
	~CardManager();
};

