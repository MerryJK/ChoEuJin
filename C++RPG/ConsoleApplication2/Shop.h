#pragma once
#include"Weapon.h"
#include"MapDraw.h"
#include"Mecro.h"
class Shop
{
private:
	static Shop* m_hThis;
	MapDraw m_DrawManager;
	Weapon* m_pWeaponList[256];
	int m_iWeaponCount;
public:
	static Shop* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new Shop;
		return m_hThis;
	}
	void ShopMenu(Character* Player);
	void WeaponMenu(Character* Player,WEAPON Type);
	string GetTypeString(WEAPON Type);
	Shop();
	~Shop();
};

