#pragma once
#include <iostream>
#include<Windows.h>
#include<string>
#include<time.h>
#include <conio.h>
using namespace std;

#define WIDTH 15
#define HEIGHT 15

#define BOMBMAX 5
#define BOMB  -1
#define FLAG -2

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define SPACE 32
#define ENTER 13

class Minesweeper
{
	int map[WIDTH][HEIGHT];
	int FlagCount;
	void InIt();
	void SetAroundBomb();
	void Play();
	void PrintAroundNum(int, int, bool);
public:
	Minesweeper();
	void MainMenu();
	~Minesweeper();
};

inline void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
