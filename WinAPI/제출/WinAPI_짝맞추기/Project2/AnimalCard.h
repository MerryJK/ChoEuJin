#pragma once
#include "resource.h"
#include "BitmapManager.h"

using namespace std;

class AnimalCard
{
	CARD_STATE m_eState;
	CARD_TYPE m_eType;
	int m_iCardXPos;
	int m_iCardYPos;
	LPCWSTR m_strAnimalName;
	Bitmap* m_pImage[2];
	RECT m_CardRect;
public:
	inline CARD_TYPE GetCardType() { return m_eType; }
	inline CARD_STATE GetCardState() { return m_eState; }
	void SetImage(CARD_TYPE);
	void SetPos(int, int);
	bool IsCardClicked(POINT);
	void ChangeState(CARD_STATE);
	void DrawCard(HDC);
	AnimalCard();
	~AnimalCard();
};

