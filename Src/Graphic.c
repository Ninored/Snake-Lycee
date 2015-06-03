#include "Graphic.h"
#include <stdlib.h>
#include <stdio.h>

#include "GameManager.h"



static Tileset *lasttileset;
static AnimationSet *lastanimset;


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
void GRAPHIC_Quit(void)
{
	IMG_Quit();
	TTF_Quit();
}


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
void GRAPHIC_FreeTexture(Texture* texture)
{
	SDL_DestroyTexture(texture->texture);
	texture->texture = NULL;
	texture->h = texture->w = 0;
}
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
void GRAPHIC_TextRight(Police *police, int posX, int posY, char* text)
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
	_pos.x -= _pos.w;

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
	lasttileset = NULL;
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
void GRAPHIC_ApplyTileRaw(Tileset *tileset, int posX, int posY, int id)
{
	if(tileset == NULL)
	{
		SDL_Rect _dst;
		_dst.x = posX;
		_dst.y = posY;
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
		_dst.x = posX;
		_dst.y = posY;
		_dst.h = tileset->tilesize;
		_dst.w = tileset->tilesize;

		SDL_RenderCopy(
				Game_GetVariables()->renderer,
				tileset->palette.texture,
				&tileset->clip.array[id],
				&_dst);

	}
}


void GRAPHIC_LoadAnimationSet(char* filename, AnimationSet* animSet, int nbAnim, int nbFramPAnim, int animSize)
{
	GRAPHIC_LoadTexture(filename, &animSet->palette);
	animSet->animationArray = (Animation*)malloc(sizeof(Animation) * nbAnim );

	animSet->animSize = animSize;
	animSet->nbAnimations = nbAnim;
	animSet->nbFramPAnim = nbFramPAnim;
	animSet->playFlag = 0x00000000; //flag
	animSet->nbAnim = nbAnim;

	unsigned int i,j;
	for(i = 0; i < nbAnim; i++)
	{
		ARRAY_CLIP_INIT(&animSet->animationArray[i].clip);
		for(j = 0; j < nbFramPAnim; j++)
		{
			ARRAY_CLIP_ADD(
					&animSet->animationArray[i].clip,
					animSize * j,
					animSize * i,
					animSize,
					animSize
			);
		}
		animSet->animationArray[i].currentFram = 0;
		animSet->animationArray[i].nbFram = nbFramPAnim;
	}

	lastanimset = animSet;
}
void GRAPHIC_FreeAnimationSet(AnimationSet* animSet)
{
	GRAPHIC_FreeTexture(&animSet->palette);
	unsigned int i;
	for(i = 0; i < animSet->nbAnim; i++)
	{
		ARRAY_CLIP_DESTROY(&animSet->animationArray[i].clip);
	}

	free(animSet->animationArray);
	lastanimset = NULL;
}
void GRAPHIC_PlayAnimation(AnimationSet *animationSet, int posX, int posY, int id)
{
	//TODO: revoir les ID pour les flag prendre une variable indépendente et la réinit
	if(animationSet == NULL)
	{
		if(id < 8)
		{
			lastanimset->playFlag ^= 1 << (id - 1) ;
			lastanimset->animationArray[id-1].currentX = posX - 1;
			lastanimset->animationArray[id-1].currentY = posY - 1;
			lastanimset->animationArray[id-1].id = id;
		}
	}
	else
	{
		if(id < 8)
		{
			animationSet->playFlag ^= 1 << (id - 1) ;
			animationSet->animationArray[id-1].currentX = posX - 1;
			animationSet->animationArray[id-1].currentY = posY - 1;
			animationSet->animationArray[id-1].id = id;
		}
	}
}
void GRAPHIC_DrawAnimation(AnimationSet *animationSet)
{
	if((animationSet->playFlag & 0x00000001) == 0x00000001)
	{
	}
	unsigned int i;
	for(i = 0; i < 8; i++)
	{
		if( (animationSet->playFlag & (1<<i)) == (1<<i))
		{

			SDL_Rect _dst;
			_dst.x = animationSet->animationArray[i].currentX * 16;// * animationSet->animSize;
			_dst.y = animationSet->animationArray[i].currentY * 16;// * animationSet->animSize;
			_dst.h = animationSet->animSize;
			_dst.w = animationSet->animSize;

			SDL_RenderCopy(
					Game_GetVariables()->renderer,
					animationSet->palette.texture,
					&animationSet->animationArray[i].clip.array[animationSet->animationArray[i].currentFram],
					&_dst);

			if(animationSet->animationArray[i].currentFram < 3)
			{
				animationSet->animationArray[i].currentFram++;
			}
			else
			{
				animationSet->animationArray[i].currentFram = 0;
				animationSet->playFlag ^= 1 << i;
				animationSet->animationArray[i].currentX = 0;
				animationSet->animationArray[i].currentY = 0;
			}
		}
	}
}
