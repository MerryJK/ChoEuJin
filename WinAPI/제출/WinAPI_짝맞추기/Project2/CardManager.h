#pragma once
#include "AnimalCard.h"
#include <vector>

class CardManager
{
private:
	HDC hdc, memDC;
	std::vector<AnimalCard*> m_vCardList;
	int m_iPreIndex;
	int m_iCurIndex;
	bool m_bIsCardMax;
public:
	void SetCardsRandImage(int num = 0);
	void SetCardsPos();
	void DrawCards(HDC);
	int CheckClickedCards(POINT);
	bool CompareCards(int, int);
	void MatchCorrectCards();
	bool WinCheck();
	void CloseCards();
	CardManager();
	~CardManager();
};

