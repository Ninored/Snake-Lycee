
#ifndef SNAKE_H_
#define SNAKE_H_

#include "Graphic.h"

typedef struct
{
	int x;
	int y;
} Position;

enum Direction {NORD, SUD, EST, OEST};

typedef struct
{
	Position Tete;
	enum Direction direction;
	int longueur;
	Position corp[100];
}Serpent;

void SERPENT_Init(Serpent *serpent);

void SERPENT_ChangeDirection(Serpent *serpent, enum Direction direction);
void SERPENT_Avancer(Serpent *serpent);
void SERPENT_GetColision(Serpent *serpent);
void SERPENT_Grow(Serpent *serpent);
void SERPENT_Draw(Serpent *serpent, Tileset *tileset);

#endif /* SNAKE_H_ */
