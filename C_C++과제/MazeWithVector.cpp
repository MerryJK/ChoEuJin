#include<iostream>
#include<vector>
#include<Windows.h>
#include<time.h>
using namespace std;

inline void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void main()
{
	srand(time(NULL));
	const int max_X = 20;
	const int max_Y = 10;

	vector<vector<int> > map;
	vector<int> x(max_X);

	for (int i = 0; i < max_Y; i++)
		map.push_back(x);

	for (int i = 0; i < max_Y; i++)
	{
		for (int j = 0; j < max_X; j++)
		{
			if (i == 0)
				map[i][j] = 1;
			else if (i == max_Y - 1)
				map[i][j] = 1;
			else
			{
				if (j == 0 || j == max_X - 1)
					map[i][j] = 1;
				else
					map[i][j] = rand() % 2;
			}
		}
		cout << endl;
	}

	for (int i = 0; i < max_Y; i++)
	{
		for (int j = 0; j < max_X; j++)
		{
			gotoxy(j * 2, i);
			if (map[i][j] == 1)
				cout << "¢Æ";
		}
		cout << endl;
	}
}