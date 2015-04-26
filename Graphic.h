/*
 * Graphic.h
 *
 *  Created on: 24 avr. 2015
 *      Author: Ulysse
 */

#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DynArray.h"

typedef struct {
	int w, h;
	SDL_Texture *texture;
}Texture;

typedef struct {
	TTF_Font *font;
}Police;

typedef struct {
	Texture palette;
	ARRAY_CLIP clip;
	int tilesize;
}Tileset;

int GRAPHIC_Init(void);
void GRAPHIC_Quit(void);

/*
 * Fonction Texture
 */
void GRAPHIC_LoadTexture(char* filename, Texture* texture);
void GRAPHIC_FreeTexture(Texture* texture);
void GRAPHIC_ApplyTexture(Texture* texture, int posX, int posY, int w, int h);

/*
 * Fonction Text
 */
void GRAPHIC_PoliceLoad(char* filename, Police *police, int size);
void GRAPHIC_Text(Police *police, int posX, int posY, char* text);
void GRAPHIC_TextAlpha(Police *police, int posX, int posY, int alpha, char* text);

/*
 * Fonction Tile
 */
void GRAPHIC_LoadTile(char* filename, Tileset *tileset, int tilesize);
void GRAPHIC_FreeTile(Tileset *tileset);
void GRAPHIC_ApplyTile(Tileset *tileset, int posX, int posY, int id);
#endif /* GRAPHIC_H_ */
