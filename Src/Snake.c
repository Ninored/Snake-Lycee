#include "Snake.h"
#include "TilesID.h"
#include "Map.h"
#include "GameManager.h"
#include "SplashScreenGameOver.h"
#include "SplashScreenPlay.h"
#include "Score.h"

void SERPENT_Init(Serpent *serpent)
{
	// Default direction
	serpent->Tete.x = 40;
	serpent->Tete.y = 22;
	serpent->direction = EST;

	// Longeur
	serpent->longueur = 2;

	serpent->corps[0].x = 40 - 1;
	serpent->corps[0].y = 22;

	serpent->corps[1].x = 40 - 2;
	serpent->corps[1].y = 22;


	serpent->Etat = NORMAL;
	serpent->compteur = 0;
	serpent->lives = 0;

	SCORE_Reset();

}

void SERPENT_Reborn(Serpent *serpent)
{
	serpent->Tete.x = 40;
	serpent->Tete.y = 22;
	serpent->direction = EST;

	// Longeur
	serpent->longueur = 2;

	serpent->corps[0].x = 40 - 1;
	serpent->corps[0].y = 22;

	serpent->corps[1].x = 40 - 2;
	serpent->corps[1].y = 22;


	serpent->Etat = NORMAL;
	serpent->compteur = 0;
}

void SERPENT_ChangeDirection(Serpent *serpent, enum Direction direction)
{
	switch(direction)
	{
	case NORD:
		if(serpent->direction != SUD) serpent->direction = direction;
		break;

	case SUD:
		if(serpent->direction != NORD) serpent->direction = direction;
		break;

	case EST:
		if(serpent->direction != OEST) serpent->direction = direction;
		break;

	case OEST:
		if(serpent->direction != EST) serpent->direction = direction;
		break;

	}
}
void SERPENT_Avancer(Serpent *serpent)
{
	unsigned int i = 0;
	for(i = serpent->longueur; i >= 1; i--)
	{
		serpent->corps[i].x = serpent->corps[i-1].x;
		serpent->corps[i].y = serpent->corps[i-1].y;
	}

	serpent->corps[0].x = serpent->Tete.x;
	serpent->corps[0].y = serpent->Tete.y;

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

	default:
		Game_Quit();
		break;
	}
}
void SERPENT_GetColision(Serpent *serpent)
{
	// Colision avec lui meme
	unsigned int i = 0;
	unsigned int j = 0;
	for(i = 0; i < serpent->longueur; i++)
	{
		if(
			serpent->Tete.x == serpent->corps[i].x &&
			serpent->Tete.y == serpent->corps[i].y
			)
		{
			serpent->lives--;
			if(serpent->lives < 0)
			{
				Game_ChangeState(SplashGameOver_Instance());
			}
			else
			{
				SERPENT_Reborn(serpent);
				Game_PushState(SplashPlay_Instance());
			}
		}
	}

	enum ITEM tmp;
	switch(serpent->Etat)
	{
	case NORMAL:
		tmp = MAP_GetColision(serpent->Tete.x, serpent->Tete.y);
		if(tmp == MURE)
		{
			serpent->lives--;
			if(serpent->lives < 0)
			{
				Game_ChangeState(SplashGameOver_Instance());
			}
			else
			{
				SERPENT_Reborn(serpent);
				Game_PushState(SplashPlay_Instance());
			}
		}
		if(tmp == POMME)
		{
			SERPENT_Grow(serpent);
			SCORE_Add(POMME);
			GRAPHIC_PlayAnimation(NULL, serpent->Tete.x, serpent->Tete.y, ANIM_POMME);
		}

		if(tmp == CERISE)
		{
			SERPENT_Grow(serpent);
			SCORE_Add(CERISE);
			GRAPHIC_PlayAnimation(NULL, serpent->Tete.x, serpent->Tete.y, ANIM_CERISE);
			serpent->Etat = ETENDU;
			serpent->compteur = 0;

		/*	if(serpent->Etat == ETENDU)
			{
				serpent->compteur++;
				if(serpent->compteur > 5)
				{
					serpent->Etat = NORMAL;
					serpent->compteur = 0;
				}
			}*/
		}

		if(tmp == COEUR)
		{
			GRAPHIC_PlayAnimation(NULL, serpent->Tete.x, serpent->Tete.y, ANIM_COEUR);
			if(serpent->lives < 3)
				serpent->lives++;
		}

		break;
	case ETENDU:
		// Tete
		tmp = MAP_GetColision(serpent->Tete.x, serpent->Tete.y);

		if(MAP_GetColision(serpent->Tete.x, serpent->Tete.y) == MURE)
		{
			serpent->lives--;
			if(serpent->lives < 0)
			{
				Game_ChangeState(SplashGameOver_Instance());
			}
			else
			{
				SERPENT_Reborn(serpent);
				Game_PushState(SplashPlay_Instance());
			}
		}
		// Autour de la tete
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				tmp = MAP_GetColision(((serpent->Tete.x - 1) + i), ((serpent->Tete.y - 1) + j));
				if(tmp == POMME)
				{
					SERPENT_Grow(serpent);
					SCORE_Add(POMME);
					GRAPHIC_PlayAnimation(NULL, serpent->Tete.x, serpent->Tete.y, ANIM_POMME);
					serpent->compteur++;
					if(serpent->compteur >= 5)
					{
						serpent->Etat = NORMAL;
						serpent->compteur = 0;
					}
				}

				else if(tmp == CERISE)
				{
					SERPENT_Grow(serpent);
					SCORE_Add(CERISE);
					GRAPHIC_PlayAnimation(NULL, serpent->Tete.x, serpent->Tete.y, ANIM_CERISE);
					serpent->compteur++;
					if(serpent->compteur > 5)
					{
						serpent->Etat = NORMAL;
						serpent->compteur = 0;
					}
				}
				else if (tmp == COEUR)
				{
					GRAPHIC_PlayAnimation(NULL, serpent->Tete.x, serpent->Tete.y, ANIM_COEUR);
					if(serpent->lives < 3)
						serpent->lives++;
				}

			}
		}
		break;

	default:
		break;
	}

}

void SERPENT_Grow(Serpent *serpent)
{
	// Augmenter la longueur du serpent
	if(serpent->longueur < 100)
	{
		serpent->longueur++;
	}
}

void SERPENT_Draw(Serpent *serpent, Tileset *tileset)
{
	unsigned int i = 0;
	switch(serpent->Etat)
	{
	case NORMAL:
		GRAPHIC_ApplyTile(tileset,serpent->Tete.x, serpent->Tete.y, TILE_TETE);
		for(i = 0; serpent->longueur > i; i++)
		{
			GRAPHIC_ApplyTile(tileset, serpent->corps[i].x, serpent->corps[i].y, TILE_CORPS);
		}
		break;

	case ETENDU:
		GRAPHIC_ApplyTile(tileset,serpent->Tete.x, serpent->Tete.y, TILE_TETE_CERISE);
		for(i = 0; serpent->longueur > i; i++)
		{
			GRAPHIC_ApplyTile(tileset, serpent->corps[i].x, serpent->corps[i].y, TILE_CORPS_CERISE);
		}
		break;
	}

}

int SERPENT_GetLives(Serpent *serpent)
{
	return serpent->lives;
}
