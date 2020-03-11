#include "Minesweeper.h"



Minesweeper::Minesweeper()
{
	srand((unsigned int)time(NULL));
}

void Minesweeper::MainMenu()
{
	char ch;
	while (1)
	{
		gotoxy(10, 3);
		cout << " 지 뢰 찾 기 ";
		gotoxy(10, 7);
		cout << "▶ 게임 시작";
		gotoxy(10, 7);
		ch = _getch();
		if (ch == ENTER)
		{
			system("cls");
			InIt();
			SetAroundBomb();
			Play();
		}
	}
}

void Minesweeper::Play()
{
	int x = 0, y = 0;
	char ch;
	while (1)
	{
		gotoxy(x * 2, y);
		ch = _getch();
		switch (ch)
		{
		case ENTER:
			if (map[y][x] == BOMB)
			{
				cout << "◎";
				gotoxy(WIDTH * 2 + 5, HEIGHT * 0.5);
				cout << "지뢰를 밟았습니다. 메인으로 돌아갑니다.";
				Sleep(3000);
				system("cls");
				return;
			}
			else
			{
				PrintAroundNum(x, y, true);
			}
			break;
		case SPACE:
			if (map[y][x] != FLAG)
			{
				cout << "¶";
				if (map[y][x] == BOMB)
				{
					FlagCount++;
					map[y][x] = FLAG;
					if (FlagCount == BOMBMAX)
					{
						gotoxy(WIDTH * 2 + 5, HEIGHT * 0.5);
						cout << "지뢰를 모두 찾았습니다. 메인으로 돌아갑니다.";
						Sleep(3000);
						system("cls");
						return;
					}
				}else
					map[y][x] = FLAG;
			}
			break;
		case UP:
			if (y > 0)
				y--;
			break;
		case DOWN:
			if (y < HEIGHT - 1)
				y++;
			break;
		case LEFT:
			if (x > 0)
				x--;
			break;
		case RIGHT:
			if (x < WIDTH - 1)
				x++;
			break;
		}
	}
}

void Minesweeper::InIt()
{
	int x;
	int y = 0;
	FlagCount = 0;

	for (int i = 0; i < WIDTH; i++)
	{
		gotoxy(0, y);
		for (int j = 0; j < HEIGHT; j++)
			cout << "□";
		y = y + 1;
	}
	cout << endl << endl <<"이동 : w  a  s  d" << endl << endl;
	cout << "지뢰 확인하기 : ENTER \t 깃발꼽기 : SPACE" << endl;

	for (int i = 0; i < BOMBMAX; i++)
	{
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		if (map[y][x] != BOMB)
			map[y][x] = BOMB;
		else
			i--;
	}
}

void Minesweeper::SetAroundBomb()
{
	int count;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			count = 0;
			if (map[i][j] != BOMB)
			{
				if (map[i][j - 1] == BOMB)
					count++;
				if (map[i - 1][j] == BOMB)
					count++;
				if (map[i - 1][j - 1] == BOMB)
					count++;
				if (map[i][j + 1] == BOMB)
					count++;
				if (map[i + 1][j] == BOMB)
					count++;
				if (map[i + 1][j + 1] == BOMB)
					count++;
				if (map[i + 1][j - 1] == BOMB)
					count++;
				if (map[i - 1][j + 1] == BOMB)
					count++;
				map[i][j] = count;
			}
		}
	}

}

void Minesweeper::PrintAroundNum(int x, int y, bool isCenter)
{
	if (map[y][x] == BOMB || map[y][x] == FLAG)
		return;
	gotoxy(x * 2, y);
	cout << map[y][x];
	
	if (!isCenter)
		return;
	//if map[y][x] 0이 아니면 뭐엿지..?
	//if map[y][x] 0이면 cout 하고 return

	if (y > 0) //북
		PrintAroundNum(x, y - 1, false);
	if (y > 0 && x % WIDTH != 0 && x != 0)	 //북서
		PrintAroundNum(x - 1, y - 1, false);
	if (y > 0 && x % WIDTH != WIDTH - 1) //북동
		PrintAroundNum(x + 1, y - 1, false);
	if (y < HEIGHT - 1)	//남
		PrintAroundNum(x, y + 1, false);
	if (y < HEIGHT - 1 && x % WIDTH != 0 && x != 0) //남서
		PrintAroundNum(x - 1, y + 1, false);
	if (y < HEIGHT - 1 && x % WIDTH != WIDTH - 1) //남동
		PrintAroundNum(x + 1, y + 1, false);
	if (x % WIDTH != WIDTH - 1) //동
		PrintAroundNum(x + 1, y, false);
	if (x % WIDTH != 0 && x != 0) //서
		PrintAroundNum(x - 1, y, false);
}

Minesweeper::~Minesweeper()
{
	
}