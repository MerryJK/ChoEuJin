#include "GameManager.h"

GameManager::GameManager()
{
	m_iPreCardType = CARD_NONE;
}

void GameManager::InIt(HWND hWnd, HINSTANCE hInst)
{
	BitmapManager::GetInstance()->Init(hWnd, hInst);
	CM.SetCardsRandImage();
	CM.SetCardsPos();
}

void GameManager::PlayGame(HWND hWnd, POINT pt)
{
	m_iCurCardType = CM.CheckClickedCards(pt);
	InvalidateRect(hWnd, NULL, true);
	if (m_iPreCardType == CARD_NONE)
	{
		InvalidateRect(hWnd, NULL, true);
		m_iPreCardType = m_iCurCardType;
		return;
	}
	else
	{
		if (CM.CompareCards(m_iPreCardType, m_iCurCardType))
		{
			CM.MatchCorrectCards();
			InvalidateRect(hWnd, NULL, true);
			if (CM.WinCheck())
			{
				if (MessageBox(hWnd, L"You Win", L"MessageBox", MB_OK) == IDOK)
					SendMessage(hWnd, WM_DESTROY, 0, 0);
			}
		}
		m_iPreCardType = CARD_NONE;
		SetTimer(hWnd, 1, 500, NULL);
	}
}

void GameManager::CloseCards(HWND hWnd)
{
	CM.CloseCards(); 
	InvalidateRect(hWnd, NULL, true);
}

void GameManager::DrawGame(HDC hdc)
{
	CM.DrawCards(hdc);
}

GameManager::~GameManager()
{
}
