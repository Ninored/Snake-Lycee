#include "Graphic.h"
#include <stdlib.h>
#include <stdio.h>

#include "GameManager.h"



static Tileset *lasttileset;

/**
 * Fonction d'initialisation de la SDL_image
 * @return Status du chargement
 */
int GRAPHIC_Init(void)
{
	int flag = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	if((flag & (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP)) != flag)
	{
		printf("[ERROR]\tError while initializing SDL_image: %s\n", IMG_GetError());
		return -1;
	}
	printf("[INFO]\tSDL_Image Loaded with flag: %d\n", flag);
	printf("[INFO]\t == See Index for flag info ==\n");

	if(TTF_Init() == -1)
	{
		printf("[ERROR]\tError while initializing SDL_ttf: %s\n", TTF_GetError());
		return -1;
	}
	printf("[INFO]\tSDL_ttf loaded\n");

	return 0;
}

/**
 * Fonction libérant la mémoire alouée par SDL_image
 */
void GRAPHIC_Quit(void)
{
	IMG_Quit();
	TTF_Quit();
}

/**
 * Fonction de chargement d'une texture
 * @param filename Fichier contenant la texture a charger
 * @param texture Structure où stoquer la texture
 */
void GRAPHIC_LoadTexture(char* filename, Texture* texture)
{
	SDL_Surface *_surface = IMG_Load(filename);
	if(_surface == NULL)
	{
		printf("[ERROR]\t|Error while loading \"%s\"\n\t|-> %s\n", filename, IMG_GetError());
		return;
	}

	texture->texture =  SDL_CreateTextureFromSurface(Game_GetVariables()->renderer, _surface);
	SDL_QueryTexture(texture->texture, NULL, NULL, &texture->w, &texture->h);

	printf("[INFO]\tTexture loaded: %s [%dx%d]\n",filename, texture->w, texture->h);
	SDL_FreeSurface(_surface);
}

/**
 * Liberation de la texture
 * @param texture Structure a libérer
 */
void GRAPHIC_FreeTexture(Texture* texture)
{
	SDL_DestroyTexture(texture->texture);
	texture->texture = NULL;
	texture->h = texture->w = 0;
}

/**
 * Application de la texture sur une position donnée avec largeur et hauteur
 * en paramètre
 * @param texture Texture a appliquer
 * @param posX Position X
 * @param posY Position Y
 * @param w Largeur
 * @param h Hauteur
 */
void GRAPHIC_ApplyTexture(Texture* texture, int posX, int posY, int w, int h)
{
	SDL_Rect tmp;
	tmp.x = posX;
	tmp.y = posY;
	tmp.w = w;
	tmp.h = h;

	SDL_RenderCopy(Game_GetVariables()->renderer, texture->texture, NULL, &tmp);

}

void GRAPHIC_ApplyTextureAlpha(Texture* texture, int posX, int posY, int w, int h, int alpha)
{
	SDL_Rect tmp;
	tmp.x = posX;
	tmp.y = posY;
	tmp.w = w;
	tmp.h = h;

	SDL_SetTextureAlphaMod(texture->texture, alpha);
	SDL_RenderCopy(Game_GetVariables()->renderer, texture->texture, NULL, &tmp);

}






void GRAPHIC_LoadPolice(char* filename, Police *police, int size)
{
	police->font = TTF_OpenFont(filename, size);
	if(police->font == NULL)
	{
		printf("[ERROR]\t|Error while charging font \"%s\":\n\t|-> %s\n", filename, TTF_GetError());
		return;
	}
	printf("[INFO]\tFont \"%s\" Loaded size : %d\n", filename, size);
}

void GRAPHIC_FreePolice(Police *police)
{
	TTF_CloseFont(police->font);
}

void GRAPHIC_Text(Police *police, int posX, int posY, char* text)
{
	SDL_Rect _pos;
	_pos.x = posX;
	_pos.y = posY;

	SDL_Color _white = {255, 255, 255};
	SDL_Surface *_surface = TTF_RenderUTF8_Solid(police->font, text, _white);

	if(_surface == NULL)
	{
		printf("[ERROR]\tError while creating font: %s\n", TTF_GetError());
		return;
	}

	SDL_Texture *_texture = SDL_CreateTextureFromSurface(Game_GetVariables()->renderer, _surface);
	SDL_QueryTexture(_texture, NULL, NULL, &_pos.w, &_pos.h);


	if(SDL_RenderCopy(Game_GetVariables()->renderer, _texture, NULL, &_pos) == -1)
	{
		printf("[ERROR]\tError while writing : %s\n", text);
		return;
	}

	SDL_FreeSurface(_surface);
	SDL_DestroyTexture(_texture);

}

void GRAPHIC_TextAlpha(Police *police, int posX, int posY, int alpha, char* text)
{
	SDL_Rect _pos;
	_pos.x = posX;
	_pos.y = posY;

	SDL_Color _white = {255, 255, 255};
	SDL_Surface *_surface = TTF_RenderUTF8_Solid(police->font, text, _white);

	if(_surface == NULL)
	{
		printf("[ERROR]\tError while creating font: %s\n", TTF_GetError());
		return;
	}



	SDL_Texture *_texture = SDL_CreateTextureFromSurface(Game_GetVariables()->renderer, _surface);
	SDL_SetTextureAlphaMod(_texture, alpha);
		SDL_QueryTexture(_texture, NULL, NULL, &_pos.w, &_pos.h);

	if(SDL_RenderCopy(Game_GetVariables()->renderer, _texture, NULL, &_pos) == -1)
	{
		printf("[ERROR]\tError while writing : %s\n", text);
		return;
	}

	SDL_FreeSurface(_surface);
	SDL_DestroyTexture(_texture);
}


void GRAPHIC_TextCentered(Police *police, int posX, int posY, char* text)
{
	SDL_Rect _pos;
	_pos.x = posX;
	_pos.y = posY;

	SDL_Color _white = {255, 255, 255};
	SDL_Surface *_surface = TTF_RenderUTF8_Solid(police->font, text, _white);

	if(_surface == NULL)
	{
		printf("[ERROR]\tError while creating font: %s\n", TTF_GetError());
		return;
	}

	SDL_Texture *_texture = SDL_CreateTextureFromSurface(Game_GetVariables()->renderer, _surface);
	SDL_QueryTexture(_texture, NULL, NULL, &_pos.w, &_pos.h);
	_pos.x -= _pos.w/2;
	_pos.y -= _pos.h/2;

	if(SDL_RenderCopy(Game_GetVariables()->renderer, _texture, NULL, &_pos) == -1)
	{
		printf("[ERROR]\tError while writing : %s\n", text);
		return;
	}

	SDL_FreeSurface(_surface);
	SDL_DestroyTexture(_texture);

}

void GRAPHIC_TextCenteredAlpha(Police *police, int posX, int posY, int alpha, char* text)
{
	SDL_Rect _pos;
	_pos.x = posX;
	_pos.y = posY;

	SDL_Color _white = {255, 255, 255};
	SDL_Surface *_surface = TTF_RenderUTF8_Solid(police->font, text, _white);

	if(_surface == NULL)
	{
		printf("[ERROR]\tError while creating font: %s\n", TTF_GetError());
		return;
	}



	SDL_Texture *_texture = SDL_CreateTextureFromSurface(Game_GetVariables()->renderer, _surface);
	SDL_SetTextureAlphaMod(_texture, alpha);
		SDL_QueryTexture(_texture, NULL, NULL, &_pos.w, &_pos.h);
	_pos.x -= _pos.w/2;
	_pos.y -= _pos.h/2;

	if(SDL_RenderCopy(Game_GetVariables()->renderer, _texture, NULL, &_pos) == -1)
	{
		printf("[ERROR]\tError while writing : %s\n", text);
		return;
	}

	SDL_FreeSurface(_surface);
	SDL_DestroyTexture(_texture);
}

void GRAPHIC_LoadTile(char* filename, Tileset *tileset, int tilesize)
{
	GRAPHIC_LoadTexture(filename, &tileset->palette);
	ARRAY_CLIP_INIT(&tileset->clip);
	tileset->tilesize = tilesize;
	unsigned int i,j;
	for(i = 0; i < tilesize; i++)
	{
		for(j = 0; j < tilesize; j++)
		{
			ARRAY_CLIP_ADD(
					&tileset->clip,
					(tileset->palette.w / tilesize) * j,
					(tileset->palette.h / tilesize) * i,
					tilesize,
					tilesize
			);
		}
	}

	lasttileset = tileset;

	printf("[INFO]\tTilesets %s: Loaded %ix%i\n", filename, tilesize, tilesize);
}

void GRAPHIC_FreeTile(Tileset *tileset)
{
	GRAPHIC_FreeTexture(&tileset->palette);
	ARRAY_CLIP_DESTROY(&tileset->clip);
}

void GRAPHIC_ApplyTile(Tileset *tileset, int posX, int posY, int id)
{
	if(tileset == NULL)
	{
		SDL_Rect _dst;
		_dst.x = posX * lasttileset->tilesize;
		_dst.y = posY * lasttileset->tilesize;
		_dst.h = lasttileset->tilesize;
		_dst.w = lasttileset->tilesize;

		SDL_RenderCopy(
				Game_GetVariables()->renderer,
				lasttileset->palette.texture,
				&lasttileset->clip.array[id],
				&_dst);
	}
	else
	{
		SDL_Rect _dst;
		_dst.x = posX * tileset->tilesize;
		_dst.y = posY * tileset->tilesize;
		_dst.h = tileset->tilesize;
		_dst.w = tileset->tilesize;

		SDL_RenderCopy(
				Game_GetVariables()->renderer,
				tileset->palette.texture,
				&tileset->clip.array[id],
				&_dst);

	}
}
