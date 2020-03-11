#include "Character.h"



Character::Character()
{
	m_pWeapon = NULL;
}

void Character::ShowInfo(int x, int y)
{
	m_DrawManager.gotoxy(x, y);
	cout << "     ======" << m_strName << "(" << m_iLv << "Lv)======" << endl;
	m_DrawManager.gotoxy(x, y + 1);
	cout << "공격력 = " << m_iDamage << "\t생명력 = " << m_iCurHealth << "/" << m_iMaxHealth << endl;
	m_DrawManager.gotoxy(x, y + 2);
	cout << "경험치 = " << m_iExp << "/" << m_iMaxExp << "\tGetEXP : " << m_iGetExp << endl;
	m_DrawManager.gotoxy(x, y + 3);
	cout << "Gold = " << m_iGold << endl;
	if (m_pWeapon)
	{
		m_pWeapon->ShowInfo(x-8, y + 4);
	}
}

void Character::Buy(Weapon* weapon)
{
	m_pWeapon = weapon;
	m_iGold -= weapon->GetGold();
}
void Character::Hit(int Damage)
{
	m_iCurHealth -= Damage;
	if (m_iCurHealth < 0)
		m_iCurHealth = 0;
}
void Character::Attack(Character* Enemy)
{
	if (m_pWeapon)
		m_pWeapon->Attack(m_iDamage, Enemy);
	else
		Enemy->Hit(m_iDamage);
}
RSP Character::GetRSP()
{
	char ch;
	if(m_eType == CHARACTER_MONSTER)	
		return (RSP)(rand() % RSP_END);
	else if (m_eType == CHARACTER_PLAYER)
	{
		while (1)
		{
			ch = getch() -49;
			if (ch >= RSP_START && ch < RSP_END)
				return (RSP)ch;
		}
	}
}
void Character::LvUp()
{
	int Num;
	PUPPLE
	m_DrawManager.BoxErase(WIDTH,HEIGHT);
	m_DrawManager.DrawMidText(m_strName + "레벨업!!", WIDTH, HEIGHT*0.4);
	Num = rand() % (UPATTACKSTAT + 1);
	m_iDamage += Num;
	m_DrawManager.DrawMidText("공격력 " + to_string(Num) + " 증가!!",WIDTH,HEIGHT*0.5);
	Num = rand() % (UPHEALTHSTAT + 1);
	m_iMaxHealth += Num;
	m_DrawManager.DrawMidText("생명력 " + to_string(Num) + " 증가!!", WIDTH, HEIGHT*0.6);
	m_iExp = 0;
	m_iMaxExp += m_iMaxExp * 0.3;
	m_iLv++;
	m_iCurHealth = m_iMaxHealth;
	ORIGINAL
}
void Character::ResetExp()
{
	m_iExp = 0;
	m_iGetExp = 0;
}

bool Character::ExpUp(Character& Enemy)
{
	int Num;
	getch();
	m_DrawManager.BoxErase(WIDTH,HEIGHT);
	m_DrawManager.DrawMidText(m_strName + " 승리!!", WIDTH, HEIGHT * 0.3);
	m_DrawManager.DrawMidText(m_strName + "가 경험치 " + to_string(Enemy.GetExp()) + "를 얻었습니다.",WIDTH,HEIGHT* 0.4);
	m_iExp += Enemy.GetExp();
	if (Enemy.GetType() == CHARACTER_PLAYER)
		Enemy.ResetExp();
	if (m_iExp >= m_iMaxExp)
	{
		getch();
		LvUp();
	}
	if (Enemy.GetType() == CHARACTER_PLAYER && Enemy.GetExp() == 0)
	{
		getch();
		m_DrawManager.DrawMidText("Game Over",WIDTH,HEIGHT*0.5);
		getch();
		return false;
	}

	if (m_eType == CHARACTER_PLAYER)
	{
		m_iGetExp = m_iExp;
		m_iGold += Enemy.GetGold();
	}
	Enemy.ResetHealth();
	getch();
	return true;
}

void Character::ResetHealth()
{
	m_iCurHealth = m_iMaxHealth;
}

void Character::Save(ofstream& Save)
{
	Save << m_strName << " ";
	Save << m_iDamage << " ";
	Save << m_iMaxHealth << " ";
	Save << m_iMaxExp << " ";
	Save << m_iGetExp << " ";
	Save << m_iLv << " ";
	Save << m_iGold << " ";
	Save << m_iExp << " ";
	Save << m_iCurHealth << endl;
	if (m_eType == CHARACTER_PLAYER)
	{
		if (m_pWeapon)
		{
			Save << 1;
			m_pWeapon->Save(Save);
		}
		else
			Save << 0;
	}
}
void Character::SetInfo(ifstream& Load, CHARACTER Type, STARTTYPE StartType)
{
	int tmp;
	string strtmp;
	string strName;
	int iDamage;
	int iGold;
	m_eType = Type;
	if (m_eType == CHARACTER_PLAYER && StartType == STARTTYPE_NEWSTART)
	{
		YELLOW
		m_DrawManager.DrawMidText("Player 이름 입력 : ", WIDTH, HEIGHT*0.5);
		cin >> m_strName;
		ORIGINAL
	}
	else
		Load >> m_strName;
	Load >> m_iDamage;
	Load >> m_iMaxHealth;
	Load >> m_iMaxExp;
	Load >> m_iGetExp;
	Load >> m_iLv;
	Load >> m_iGold;
	if (StartType == STARTTYPE_LOADSTART)
	{
		Load >> m_iExp;
		Load >> m_iCurHealth;
		if (m_eType == CHARACTER_PLAYER)
		{
			Load >> tmp;
			if (tmp)
			{
				Load >> strtmp;
				Load >> strName;
				Load >> iDamage;
				if (strtmp == "대거")
					m_pWeapon = new Dagger(strName, iDamage, iGold);
				else if (strtmp == "총")
					m_pWeapon = new Gun(strName, iDamage, iGold);
				else if (strtmp == "장검")
					m_pWeapon = new Sword(strName, iDamage, iGold);
				else if (strtmp == "지팡이")
					m_pWeapon = new Wand(strName, iDamage, iGold);
				else if (strtmp == "활")
					m_pWeapon = new Bow(strName, iDamage, iGold);
				else if (strtmp == "망치")
					m_pWeapon = new Hammer(strName, iDamage, iGold);
			}
		}
	}
	else
	{
		m_iExp = 0;
		ResetHealth();
	}
}

void Character::DeleteWeapon()
{
	if (m_pWeapon)
		delete m_pWeapon;
}

Character::~Character()
{
	DeleteWeapon();
}
