#pragma once
#include "resource.h"
#include<Windows.h>
#include<iostream>
using namespace std;

class AnimalCard
{
	bool m_IsBack;
	int m_iCardXPos;
	int m_iCardYPos;
	int m_iCardCode;
	LPCWSTR m_strAnimalName;
	HBITMAP m_MyBitmap;
	HBITMAP m_OldBitmap;
public:
	AnimalCard(int, int, int);
	void DrawCard(HDC, HDC, PAINTSTRUCT, HINSTANCE);
	void CheckClicked(HWND, int, int);
	AnimalCard();
	~AnimalCard();
};

