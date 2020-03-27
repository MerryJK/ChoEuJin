#include "CardManager.h"

CardManager::CardManager()
{
	m_iPreIndex = CARD_NONE;
	for (int i = 0; i < CARD_MAX; i++)
		m_vCardList.push_back(new AnimalCard);
	m_bIsCardMax = false;
}

void CardManager::SetCardsRandImage(int num)
{
	int cardType[CARD_END];
	int index = num;
	bool isSame;
	for (int i = 0; i < CARD_END; i++)
	{
		while (true)
		{
			isSame = false;
			cardType[i] = (rand() % 10) + 101;
			for (int j = 0; j < i; j++)
			{
				if (cardType[j] == cardType[i])
				{
					isSame = true;
					break;
				}
			}
			if (!isSame)
				break;
		}
	}
	for (int i = 0; i < CARD_END; i++)
	{
		m_vCardList[index]->SetImage((CARD_TYPE)cardType[i]);
		index++;
	}
	if (!m_bIsCardMax)
	{
		m_bIsCardMax = true;
		SetCardsRandImage(CARD_END);
	}
}

void CardManager::SetCardsPos()
{
	int x = 20;
	int y = 20;
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			x += 100;
			m_vCardList[count]->SetPos(x, y);
			count++;
		}
		x = 20;
		y += 180;
	}
}

void CardManager::DrawCards(HDC hdc)
{
	for (auto iter = m_vCardList.begin(); iter != m_vCardList.end(); iter++)
		(*iter)->DrawCard(hdc);
}

int CardManager::CheckClickedCards(POINT pt)
{
	for (int i = 0; i < CARD_MAX; i++)
	{
		if (m_vCardList[i]->GetCardState() != CARD_DONE && m_vCardList[i]->IsCardClicked(pt))
		{
			m_vCardList[i]->ChangeState(CARD_OPEN);
			if (m_iPreIndex == CARD_NONE)
				m_iPreIndex = i;
			else
				m_iCurIndex = i;
			return m_vCardList[i]->GetCardType();
		}
	}
	return CARD_NONE;
}

bool CardManager::CompareCards(int card1, int card2)
{
	if (card1 == card2)
		return true;
	return false;
}

void CardManager::MatchCorrectCards()
{
	m_vCardList[m_iPreIndex]->ChangeState(CARD_DONE);
	m_vCardList[m_iCurIndex]->ChangeState(CARD_DONE);
	m_iPreIndex = CARD_NONE;
}

void CardManager::CloseCards()
{
	if (m_vCardList[m_iPreIndex]->GetCardState() != CARD_DONE && m_vCardList[m_iCurIndex]->GetCardState() != CARD_DONE)
	{
		m_vCardList[m_iPreIndex]->ChangeState(CARD_CLOSE);
		m_vCardList[m_iCurIndex]->ChangeState(CARD_CLOSE);
	}
	m_iPreIndex = CARD_NONE;
}

bool CardManager::WinCheck()
{
	for (auto iter = m_vCardList.begin(); iter != m_vCardList.end(); iter++)
	{
		if ((*iter)->GetCardState() != CARD_DONE)
			return false;
	}
	return true;
}


CardManager::~CardManager()
{
}
