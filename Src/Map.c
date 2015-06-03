#include "Map.h"
#include "Graphic.h"
#include "GameManager.h"
#include "TilesID.h"
#include <time.h>

static enum ITEM Map[MAP_W][MAP_H];
static bool present;

void MAP_Init(void)
{

	srand(time(NULL));
	//srand(1);
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
	// Gestion hors map
	if( ((posX < 0) | (posX > 80)) &&
		((posY < 0) | (posY > 45))
	) return VIDE;

	enum ITEM tmp = Map[posX][posY];
	switch(tmp)
	{

	case CERISE:
	case POMME:
	case COEUR:
		Map[posX][posY] = VIDE;
		present = false;
		return tmp;
		break;
	case MURE:
		return MURE;
		break;

	default:
		return VIDE;
		break;
	}

	return VIDE;
}

void MAP_GenerateRandomeItem(void)
{
	if(!present)
	{
		float randomNum = (double)rand()/(double)RAND_MAX;
		if(randomNum < 0.02)
		{
			int posX = (rand() % 78) + 1;
			int posY = (rand() % 41) + 3;
			Map[posX][posY] = COEUR;
			present = true;
		}
		else if(randomNum < 0.10)
		{
			int posX = (rand() % 78) + 1;
			int posY = (rand() % 41) + 3;
			Map[posX][posY] = CERISE;
			present = true;
		}

		else if(randomNum < 0.88)
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
			if(Map[i][j] == POMME) GRAPHIC_ApplyTile(NULL, i, j, TILE_POMME);
			if(Map[i][j] == CERISE) GRAPHIC_ApplyTile(NULL, i, j, TILE_CERISE);
			if(Map[i][j] == COEUR) GRAPHIC_ApplyTile(NULL, i, j, TILE_COEUR);
		}
	}
}
