#include "GameManager.h"

GameManager* GameManager::m_hThis = NULL;

GameManager::GameManager()
{
	m_bGameExit = false;
	m_pMonster = NULL;
	m_pPlayer = NULL;
	m_iMonsterCount = 0;
}

bool GameManager::Init(STARTTYPE StartType)
{
	Delete();
	switch (StartType)
	{
	case STARTTYPE_NEWSTART:
		m_strPlayerFileName = "DefaultPlayer.txt";
		m_strMonsterFileName = "DefaultMonster.txt";
		break;
	case STARTTYPE_LOADSTART:
		if (!FileList(FILESTATE_LOAD))
			return false;
		break;
	}
	return Load(StartType);
}

void GameManager::RSPDraw(RSP Rsp, int x, int y)
{
	m_DrawManager.DrawMidText("        ", x, y);
	switch (Rsp)
	{
	case RSP_ROCK:
		m_DrawManager.DrawMidText("바위", x, y);
		break;
	case RSP_SCISSOR:
		m_DrawManager.DrawMidText("가위", x, y);
		break;
	case RSP_PAPER:
		m_DrawManager.DrawMidText("보", x, y);
		break;
	default:
		break;
	}
}
void GameManager::Fight(Character* Player, Character* Monster)
{
	bool GameEnd = false;
	RSP PlayerRsp,MonsterRsp;
	m_DrawManager.BoxErase(WIDTH, HEIGHT);
	while (1)
	{
		YELLOW
		Player->ShowInfo(WIDTH - 15, HEIGHT * 0.1);
		m_DrawManager.DrawMidText("가위 : 1   바위 : 2   보 : 3", WIDTH, HEIGHT*0.3);
		ORIGINAL
		Monster->ShowInfo(WIDTH - 15, HEIGHT * 0.8);
		RED
		m_DrawManager.DrawMidText("-------------------------- vs --------------------------", WIDTH, HEIGHT*0.5);
		if (Player->GetHealth() == 0)
		{
			if (!Monster->ExpUp(*Player))
				m_bGameExit = true;
			return;
		}
		else if (Monster->GetHealth() == 0)
		{
			Player->ExpUp(*Monster);
			return;
		}
		PlayerRsp = Player->GetRSP();
		m_DrawManager.BoxErase(WIDTH, HEIGHT);
		YELLOW
		RSPDraw(PlayerRsp, WIDTH, HEIGHT*0.4);
		MonsterRsp = Monster->GetRSP();
		ORIGINAL
		RSPDraw(MonsterRsp, WIDTH, HEIGHT*0.65);
		RED
		if (PlayerRsp > MonsterRsp)
		{
			if (PlayerRsp == RSP_PAPER && MonsterRsp == RSP_SCISSOR)
			{
				m_DrawManager.DrawMidText("Win", WIDTH, HEIGHT*0.6);
				m_DrawManager.DrawMidText("Lose", WIDTH, HEIGHT*0.45);
				Monster->Attack(Player);
			}
			else
			{
				m_DrawManager.DrawMidText("Win", WIDTH, HEIGHT*0.45);
				m_DrawManager.DrawMidText("Lose", WIDTH, HEIGHT*0.6);
				Player->Attack(Monster);
			}
		}
		else if (PlayerRsp < MonsterRsp)
		{
			if (PlayerRsp == RSP_SCISSOR && MonsterRsp == RSP_PAPER)
			{
				m_DrawManager.DrawMidText("Win", WIDTH, HEIGHT*0.45);
				m_DrawManager.DrawMidText("Lose", WIDTH, HEIGHT*0.6);
				Player->Attack(Monster);
			}
			else
			{
				m_DrawManager.DrawMidText("Win", WIDTH, HEIGHT*0.6);
				m_DrawManager.DrawMidText("Lose", WIDTH, HEIGHT*0.45);
				Monster->Attack(Player);
			}
		}
		else
		{
			m_DrawManager.DrawMidText("Draw", WIDTH, HEIGHT*0.45);
			m_DrawManager.DrawMidText("Draw", WIDTH, HEIGHT*0.6);
		}
		ORIGINAL

	}
}
void GameManager::Dongeon()
{
	char buf[256];
	m_DrawManager.BoxErase(WIDTH,HEIGHT);
	BLOOD
	m_DrawManager.DrawMidText("=====던전 입구=====  ",WIDTH,HEIGHT*0.2);
	int i;
	int y = HEIGHT * 0.5 - (m_iMonsterCount / 2) * 2;
	int MaxNameLen = 0;
	for (i = 1; i <= m_iMonsterCount; i++)
	{
		sprintf(buf, "%d층던전 : [%s]", i, m_pMonster[i-1].GetName().c_str());
		if (MaxNameLen < m_pMonster[i - 1].GetName().length())
			MaxNameLen = m_pMonster[i - 1].GetName().length();
		m_DrawManager.DrawMidText(buf, WIDTH, y + i * 2);
	}	
	m_DrawManager.DrawMidText("돌아가기",WIDTH, y + i * 2);
	ORIGINAL
	int Select = m_DrawManager.MenuSelectCursor(m_iMonsterCount+1, 2, (WIDTH - strlen(buf) / 2 - MaxNameLen/2) / 2, y + 2);
	if (Select == m_iMonsterCount+ 1)
		return;
	else if (Select >= 1 && Select <= m_iMonsterCount)
		Fight(m_pPlayer,&m_pMonster[Select - 1]);
}
void GameManager::Save()
{
	FileList(FILESTATE_SAVE);
	ofstream Save;
	Save.open(m_strPlayerFileName);
	m_pPlayer->Save(Save);
	Save.close();
	Save.open(m_strMonsterFileName);
	Save << m_iMonsterCount << endl;
	for (int i = 0; i < m_iMonsterCount; i++)
		m_pMonster[i].Save(Save);
}
bool GameManager::Load(STARTTYPE StartType)
{
	m_DrawManager.BoxErase(WIDTH,HEIGHT);
	ifstream Load;
	Load.open(m_strPlayerFileName);
	if (!Load.is_open())
	{
		cout << "Player정보 없음" << endl;
		return false;
	}
	m_pPlayer = new Character;
	m_pPlayer->SetInfo(Load, CHARACTER_PLAYER,StartType);
	Load.close();
	Load.open(m_strMonsterFileName);
	if (!Load.is_open())
	{
		cout << "Monster정보 없음" << endl;
		return false;
	}
	Load >> m_iMonsterCount;
	m_pMonster = new Character[m_iMonsterCount];
	for (int i = 0; i < m_iMonsterCount; i++)
		m_pMonster[i].SetInfo(Load, CHARACTER_MONSTER,StartType);
	Load.close();
	return true;
}

bool GameManager::FileList(FILESTATE State)
{
	int Select,i;
	ifstream F1,F2;
	char buf[256],ch;
	bool FileState[10];
	while (1)
	{
		GREEN
		m_DrawManager.BoxErase(WIDTH, HEIGHT);
		for (i = 1; i <= 10; i++)
		{
			sprintf(buf, "SavePlayer%d.txt", i);
			F1.open(buf);
			sprintf(buf, "SaveMonster%d.txt", i);
			F2.open(buf);
			if (F1.is_open() && F2.is_open())
			{
				ch = 'O';
				FileState[i - 1] = true;
			}
			else
			{
				ch = 'X';
				FileState[i - 1] = false;
			}
			sprintf(buf, "%d번슬롯 : (파일여부 : %c)",i ,ch);
			m_DrawManager.DrawMidText((string)buf, WIDTH, HEIGHT* 0.1 + i*2);
			F1.close();
			F2.close();
		}
		m_DrawManager.DrawMidText("11.돌아가기             ", WIDTH, HEIGHT* 0.1 + i++ * 2);
		Select = m_DrawManager.MenuSelectCursor(11, 2, (WIDTH - strlen(buf)/2 - 3)/2, HEIGHT* 0.1 + 2);
		m_DrawManager.BoxErase(WIDTH, HEIGHT);
		string str;
		if (State == FILESTATE_SAVE)
			str = "Save 완료";
		else if (State == FILESTATE_LOAD)
			str = "Load 완료";
		ORIGINAL
		if (Select >= 1 && Select <= 10)
		{
			if ((State == FILESTATE_LOAD && FileState[Select - 1]) || State == FILESTATE_SAVE)
			{
				sprintf(buf, "SavePlayer%d.txt", Select);
				m_strPlayerFileName = buf;
				sprintf(buf, "SaveMonster%d.txt", Select);
				m_strMonsterFileName = buf;
				m_DrawManager.DrawMidText(str, WIDTH, HEIGHT*0.5);
				getch();
				return true;
			}
			else
				m_DrawManager.DrawMidText("해당 파일이 없습니다.", WIDTH, HEIGHT*0.5);
		}
		else if (Select == 11)
			return false;
		m_DrawManager.gotoxy(WIDTH/2, HEIGHT*0.5+1);
		system("pause");
	}
	ORIGINAL
	return false;
}
void GameManager::Play()
{
	while (!m_bGameExit)
	{
		m_DrawManager.BoxErase(WIDTH, HEIGHT);
		RED
		m_DrawManager.DrawMidText("☆★ Menu ★☆", WIDTH, HEIGHT* 0.3);
		m_DrawManager.DrawMidText("Dongeon", WIDTH, HEIGHT* 0.3 + 2);
		m_DrawManager.DrawMidText("Player Info", WIDTH, HEIGHT* 0.3 + 4);
		m_DrawManager.DrawMidText("Monster Info", WIDTH, HEIGHT* 0.3 + 6);
		m_DrawManager.DrawMidText("Weapon Shop", WIDTH, HEIGHT* 0.3 + 8);
		m_DrawManager.DrawMidText("Save", WIDTH, HEIGHT* 0.3 + 10);
		m_DrawManager.DrawMidText("Exit", WIDTH, HEIGHT* 0.3 + 12);
		ORIGINAL
		int y;
		switch (m_DrawManager.MenuSelectCursor(6, 2, (WIDTH - strlen("Monster Info") / 2 - 3) / 2, HEIGHT* 0.3 + 2))
		{
		case 1:
			Dongeon();
			break;
		case 2:
			YELLOW
			m_DrawManager.BoxErase(WIDTH, HEIGHT);
			m_pPlayer->ShowInfo(WIDTH - 15, HEIGHT * 0.5);
			ORIGINAL
			getch();
			break;
		case 3:
			m_DrawManager.BoxErase(WIDTH, HEIGHT);
			y = HEIGHT * 0.5 - (m_iMonsterCount/2) * 4;
			for (int i = 0; i < m_iMonsterCount; i++)
				m_pMonster[i].ShowInfo(WIDTH - 15, y + i * 4);
			getch();
			break;
		case 4:
			Shop::GetInstance()->ShopMenu(m_pPlayer);
			//m_Shop.ShopMenu(m_pPlayer);
			break;
		case 5:
			Save();
			break;
		case 6:
			return;
		}
	}
	m_bGameExit = false;
}


void GameManager::TitleDraw()
{
	RED
	m_DrawManager.DrawMidText("☆★ DonGeonRPG ★☆", WIDTH, HEIGHT* 0.4);
	m_DrawManager.DrawMidText("New Game", WIDTH, HEIGHT* 0.4 + 3);
	m_DrawManager.DrawMidText("Load Game", WIDTH, HEIGHT* 0.4 + 6);
	m_DrawManager.DrawMidText("Game Exit", WIDTH, HEIGHT* 0.4 + 9);
	ORIGINAL
}

void GameManager::GameTitleScene()
{
	srand(time(NULL));
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", HEIGHT + 1, WIDTH * 2);
	system(buf);
	BLUE
		m_DrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
	while (1)
	{
		m_DrawManager.BoxErase(WIDTH,HEIGHT);
		TitleDraw();
		switch (m_DrawManager.MenuSelectCursor(3, 3, (WIDTH - strlen("Game Exit")/2 - 3)/2, HEIGHT* 0.4 + 3))
		{
		case 1:
			if (Init(STARTTYPE_NEWSTART))
				Play();
			break;
		case 2:
			if (Init(STARTTYPE_LOADSTART))
				Play();
			break;
		case 3:
			return;
		}
	}
}
void GameManager::Delete()
{
	if (m_pMonster)
		delete[] m_pMonster;
	if (m_pPlayer)
		delete m_pPlayer;
}
GameManager::~GameManager()
{
	Delete();
}
