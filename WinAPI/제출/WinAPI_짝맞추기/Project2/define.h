#pragma once
#include <Windows.h>
#include <vector>
#include <time.h>

enum CARD_TYPE
{
	CARD_DOG = 101,
	CARD_TIGER,
	CARD_DUCK,
	CARD_ELEPHANT,
	CARD_COW,
	CARD_HORSE,
	CARD_CAT,
	CARD_MONKEY,
	CARD_FROG,
	CARD_CHICKEN,
	CARD_BACK
};

enum CARD_STATE
{
	CARD_OPEN,
	CARD_CLOSE,
	CARD_DONE,
	CARD_NONE,
	CARD_END = 10,
	CARD_MAX = 20
};