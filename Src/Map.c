#include "Map.h"
#include "Graphic.h"
#include "GameManager.h"

static enum ITEM Map[MAP_W][MAP_H];


static bool RandProb(float prob);
static bool present;

void MAP_Init(void)
{
	//srand(time(NULL));
	srand(1);
	unsigned int i,j;
	for(i = 0; i < MAP_W; i++)
		for(j = 0; j < MAP_H; j++)
			Map[i][j] = VIDE;

	for(i = 0 ; i < MAP_W; i++)
	{
		Map[i][2] = MURE;
		Map[i][44] = MURE;
	}

	for(i = 0; i < MAP_H; i++)
	{
		Map[0][i] = MURE;
		Map[79][i] = MURE;
	}
	present = false;
}

enum ITEM MAP_GetColision(int posX, int posY)
{
	enum ITEM tmp;
	tmp = Map[posX][posY];
	if(tmp != VIDE)
	{
		Map[posX][posY] = VIDE;
		present = false;
	}
	return tmp;
}

void MAP_GenerateRandomeItem(void)
{
	if(!present)
	{

		if(RandProb(0.8))
		{
			int posX = (rand() % 78) + 1;
			int posY = (rand() % 41) + 3;
			Map[posX][posY] = POMME;
			present = true;
		}
	}
}

void MAP_Draw(void)
{
	unsigned int i,j;
	for(i = 0; i < MAP_W; i++)
	{
		for(j = 0; j < MAP_H; j++)
		{
			if(Map[i][j] == POMME) GRAPHIC_ApplyTile(NULL, i, j, 5);
		}
	}
}

bool RandProb( float prob)
{
	return rand() < prob * ((float)RAND_MAX + 1.0);
}
