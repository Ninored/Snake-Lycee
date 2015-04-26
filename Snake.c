#include "Snake.h"
#include "TilesID.h"

void SERPENT_Init(Serpent *serpent)
{
	serpent->Tete.x = 40;
	serpent->Tete.y = 22;
	serpent->direction = EST;

	serpent->longueur = 2;

	serpent->corp[0].x = 40 - 1;
	serpent->corp[0].y = 22;

	serpent->corp[1].x = 40 - 2;
	serpent->corp[1].y = 22;

}
void SERPENT_Free(Serpent *serpent)
{

}


void SERPENT_ChangeDirection(Serpent *serpent, enum Direction direction)
{
	serpent->direction = direction;
}
void SERPENT_Avancer(Serpent *serpent)
{
	unsigned int i = 0;
	for(i = serpent->longueur; i >= 1; i--)
	{
		serpent->corp[i].x = serpent->corp[i-1].x;
		serpent->corp[i].y = serpent->corp[i-1].y;
	}

	serpent->corp[0].x = serpent->Tete.x;
	serpent->corp[0].y = serpent->Tete.y;

	switch(serpent->direction)
	{
	case NORD:
		serpent->Tete.y--;
		break;
	case SUD:
		serpent->Tete.y++;
		break;
	case EST:
		serpent->Tete.x++;
		break;
	case OEST:
		serpent->Tete.x--;
		break;
	}
}
void SERPENT_GetColision(Serpent *serpent)
{
	// Colision avec lui meme
/*	unsigned int i= 0;
	for(i = 0; i < serpent->longueur; i++)
	{
		if(
				serpent->Tete.x == serpent->corp[i].x &&
				serpent->Tete.y == serpent->corp[i].y
				)

	}
	*/
}
void SERPENT_Draw(Serpent *serpent, Tileset *tileset)
{
	unsigned int i = 0;
	for(i = 0; serpent->longueur > i; i++)
	{
		GRAPHIC_ApplyTile(tileset, serpent->corp[i].x, serpent->corp[i].y, TILE_CORPS);
	}

	GRAPHIC_ApplyTile(tileset,serpent->Tete.x, serpent->Tete.y, TILE_TETE);
}
