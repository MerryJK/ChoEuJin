#include "Shop.h"

Shop* Shop::m_hThis = NULL;

Shop::Shop()
{
	m_iWeaponCount = 0;
	ifstream Load;
	string strName;
	string strType;
	int iDamage;
	int iGold;
	Load.open("WeaponList.txt");
	if (Load.is_open())
	{
		while (!Load.eof())
		{
			Load >> strType;
			Load >> strName;
			Load >> iDamage;
			Load >> iGold;
			if (strType == "Bow")
				m_pWeaponList[m_iWeaponCount] = new Bow(strName, iDamage, iGold);
			else if (strType == "Hammer")
				m_pWeaponList[m_iWeaponCount] = new Hammer(strName, iDamage, iGold);
			else if (strType == "Dagger")
				m_pWeaponList[m_iWeaponCount] = new Dagger(strName, iDamage, iGold);
			else if (strType == "Gun")
				m_pWeaponList[m_iWeaponCount] = new Gun(strName, iDamage, iGold);
			else if (strType == "Sword")
				m_pWeaponList[m_iWeaponCount] = new Sword(strName, iDamage, iGold);
			else if (strType == "Wand")
				m_pWeaponList[m_iWeaponCount] = new Wand(strName, iDamage, iGold);
			m_iWeaponCount++;
		}
	}
}

void Shop::ShopMenu(Character* Player)
{
	int index;
	while (1)
	{
		m_DrawManager.BoxErase(WIDTH, HEIGHT);
		m_DrawManager.DrawMidText("♧ ♣ S H O P ♣ ♧", WIDTH, HEIGHT*0.3);
		m_DrawManager.DrawMidText("Dagger", WIDTH, HEIGHT*0.3 + 2);
		m_DrawManager.DrawMidText("Gun", WIDTH, HEIGHT*0.3 + 4);
		m_DrawManager.DrawMidText("Sword", WIDTH, HEIGHT*0.3 + 6);
		m_DrawManager.DrawMidText("Wand", WIDTH, HEIGHT*0.3 + 8);
		m_DrawManager.DrawMidText("Bow", WIDTH, HEIGHT*0.3 + 10);
		m_DrawManager.DrawMidText("Hammer", WIDTH, HEIGHT*0.3 + 12);
		m_DrawManager.DrawMidText("돌아가기", WIDTH, HEIGHT*0.3 + 14);
		index = m_DrawManager.MenuSelectCursor(7, 2, (WIDTH - strlen("Hammer") / 2 - 3) / 2, HEIGHT*0.3 + 2);
		if (index == 7)
			return;
		else
			WeaponMenu(Player,(WEAPON)(index - 1));
	}
}

string Shop::GetTypeString(WEAPON Type)
{
	switch (Type)
	{
	case WEAPON_DAGGER:
		return "Dagger";
	case WEAPON_GUN:
		return "Gun";
	case WEAPON_SWORD:
		return "Sword";
	case WEAPON_WAND:
		return "Wand";
	case WEAPON_BOW:
		return "Bow";
	case WEAPON_HAMMER:
		return "Mammer";
	}
}
void Shop::WeaponMenu(Character* Player,WEAPON Type)
{
	int Page = 0, i = 0, count = 0;
	bool PageFlag;
	int index, NextIndex, BeforeIndex, MenuCount = 0,Line;
	int y = HEIGHT *0.2;
	int arrindex[5];
	while (1)
	{
		Line = 0;
		count = 0;
		MenuCount = 0;
		m_DrawManager.BoxErase(WIDTH, HEIGHT);
		m_DrawManager.DrawMidText("보유 Gold : " + to_string(Player->GetGold()), WIDTH, y - 4);
		m_DrawManager.DrawMidText(GetTypeString(Type) + " Shop", WIDTH, y - 2);
		for (i = 0; i < m_iWeaponCount; i++)
		{
			if (m_pWeaponList[i]->GetType() == Type)
			{
				if (count >= Page && count < Page + 5)
				{
					m_pWeaponList[i]->ShowShopInfo(WIDTH, y + Line++ * 3);
					arrindex[MenuCount] = i;
					MenuCount++;
				}
				count++;
			}
		}
		if (count > Page + 5)
			PageFlag = true;
		else
			PageFlag = false;
		m_DrawManager.DrawMidText("이전페이지", WIDTH, y + Line++ * 3);
		m_DrawManager.DrawMidText("다음페이지", WIDTH, y + Line++ * 3);
		m_DrawManager.DrawMidText("나가기", WIDTH, y + Line * 3);
		MenuCount += 3;
		index = m_DrawManager.MenuSelectCursor(MenuCount, 3, 5,y);
		if (index == MenuCount)
			return;
		else if (index == MenuCount - 1 && PageFlag)
			Page += 5;
		else if (index == MenuCount - 2 && Page - 5 >= 0)
			Page -= 5;
		else if(index >= 1 && index <= MenuCount - 3)
		{
			if (Player->GetGold() >= m_pWeaponList[arrindex[index - 1]]->GetGold())
			{
				Weapon* weapon;
				switch (Type)
				{
				case WEAPON_DAGGER:
					Player->Buy(new Dagger((Dagger*)(m_pWeaponList[arrindex[index - 1]])));
					break;
				case WEAPON_GUN:
					Player->Buy(new Gun((Gun*)(m_pWeaponList[arrindex[index - 1]])));
					break;
				case WEAPON_SWORD:
					Player->Buy(new Sword((Sword*)(m_pWeaponList[arrindex[index - 1]])));
					break;
				case WEAPON_WAND:
					Player->Buy(new Wand((Wand*)(m_pWeaponList[arrindex[index - 1]])));
					break;
				case WEAPON_BOW:
					Player->Buy(new Bow((Bow*)(m_pWeaponList[arrindex[index - 1]])));
					break;
				case WEAPON_HAMMER:
					Player->Buy(new Hammer((Hammer*)(m_pWeaponList[arrindex[index - 1]])));
					break;
				}
			}
		}
	}
}


Shop::~Shop()
{
}
