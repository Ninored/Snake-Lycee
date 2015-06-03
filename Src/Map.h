#ifndef MAP_H_
#define MAP_H_

enum ITEM { VIDE = 0, MURE, POMME, CERISE, COEUR};


void MAP_Init(void);
enum ITEM MAP_GetColision(int posX, int posY);
void MAP_GenerateRandomeItem(void);
void MAP_Draw(void);

#endif /* MAP_H_ */
