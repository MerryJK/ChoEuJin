#include "AnimalCard.h"

AnimalCard::AnimalCard()
{
	m_eState = CARD_CLOSE;
}

void AnimalCard::SetImage(CARD_TYPE index)
{
	m_eType = index;
	m_pImage[CARD_OPEN] = BitmapManager::GetInstance()->GetImage(index);
	m_pImage[CARD_CLOSE] = BitmapManager::GetInstance()->GetBackCard();
}

void AnimalCard::SetPos(int xPos, int yPos)
{
	m_iCardXPos = xPos;
	m_iCardYPos = yPos;
	m_CardRect.left = xPos;
	m_CardRect.right = xPos + m_pImage[CARD_CLOSE]->GetSize().cx * 0.5f;
	m_CardRect.top = yPos;
	m_CardRect.bottom = yPos + m_pImage[CARD_CLOSE]->GetSize().cy * 0.5f;
}

void AnimalCard::DrawCard(HDC hdc)
{
	if (m_eState == CARD_CLOSE)
		m_pImage[CARD_CLOSE]->Draw(hdc, m_iCardXPos, m_iCardYPos);
	else
		m_pImage[CARD_OPEN]->Draw(hdc, m_iCardXPos, m_iCardYPos);
}

bool AnimalCard::IsCardClicked(POINT pt)
{
	if (PtInRect(&m_CardRect, pt))
	{
		if (m_eState == CARD_CLOSE)
		{
			m_eState = CARD_OPEN;
			return true;
		}
	}
	return false;
}

void AnimalCard::ChangeState(CARD_STATE state)
{
	m_eState = state;
}

AnimalCard::~AnimalCard()
{
}
