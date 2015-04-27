#ifndef MAP_H_
#define MAP_H_

enum ITEM { VIDE, MURE, POMME};


void MAP_Init(void);
enum ITEM MAP_GetColision(int posX, int posY);
void MAP_GenerateRandomeItem(void);
void MAP_Draw(void);

#endif /* MAP_H_ */
