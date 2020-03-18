#include "CardManager.h"

CardManager* CardManager::CM = NULL;

CardManager::CardManager()
{
}

void CardManager::SetCards()
{
	int addXPos = 0;
	int addYPos = 0;
	int addCardNum = 0;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				m_vCardList.push_back(new AnimalCard(20 +addXPos, 20+addYPos, 101 + addCardNum));
				addXPos += 150;
				addCardNum++;
			}
			addXPos = 0;
			addYPos += 270;
		}
}

void CardManager::DrawCards(HWND hWnd, HINSTANCE g_hInst)
{
	hdc = BeginPaint(hWnd, &ps);
	for (auto iter = m_vCardList.begin(); iter != m_vCardList.end(); iter++)
		(*iter)->DrawCard(hdc, memDC, ps, g_hInst);
	EndPaint(hWnd, &ps);
}

void CardManager::CheckClickedCards(HWND hWnd, int x, int y)
{
	for (auto iter = m_vCardList.begin(); iter != m_vCardList.end(); iter++)
		(*iter)->CheckClicked(hWnd, x, y);
}

CardManager::~CardManager()
{
}
