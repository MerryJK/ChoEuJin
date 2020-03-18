#include "AnimalCard.h"

AnimalCard::AnimalCard()
{
}

AnimalCard::AnimalCard(int x, int y, int cardNum):m_iCardXPos(x), m_iCardYPos(y), m_iCardCode(cardNum)
{
	m_IsBack = true;
	switch (m_iCardCode)
	{
	case 101:
		m_strAnimalName = "������";
		break;
	case 102:
		m_strAnimalName = "ȣ����";
		break;
	case 103:
		m_strAnimalName = "����";
		break;
	case 104:
		m_strAnimalName = "�ڳ���";
		break;
	case 105:
		m_strAnimalName = "��";
		break;
	case 106:
		m_strAnimalName = "��";
		break;
	case 107:
		m_strAnimalName = "�����";
		break;
	case 108:
		m_strAnimalName = "������";
		break;
	case 109:
		m_strAnimalName = "������";
		break;
	case 110:
		m_strAnimalName = "��";
		return;
	}
}

void AnimalCard::DrawCard(HDC hdc, HDC memDC, PAINTSTRUCT ps, HINSTANCE g_hInst)
{
	memDC = CreateCompatibleDC(hdc);
	//if (m_IsBack)
		//m_MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(111));
	//else
		m_MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(m_iCardCode));
	//m_MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(CardName));
	m_OldBitmap = (HBITMAP)SelectObject(memDC, m_MyBitmap);
	BitBlt(hdc, m_iCardXPos, m_iCardYPos, 145, 235, memDC, 0, 0, SRCCOPY);
	//StretchBlt(hdc, m_iCardXPos, m_iCardYPos, 73, 120, memDC,0,0, 145, 235, SRCCOPY);
	SelectObject(memDC, m_OldBitmap);
	DeleteObject(m_MyBitmap);
	DeleteDC(memDC);
}

void AnimalCard::CheckClicked(HWND hWnd, int x, int y)
{
	if (x > m_iCardXPos && x < m_iCardXPos + 145 && y<m_iCardYPos + 235 && y > m_iCardYPos)
	{
		//m_IsBack = false;
		MessageBox(hWnd, TEXT(m_strAnimalName), TEXT("MessageBox"), MB_OK);
		InvalidateRect(hWnd, NULL, TRUE);
	}
}

AnimalCard::~AnimalCard()
{
}
