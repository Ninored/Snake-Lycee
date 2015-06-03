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
#include <stdbool.h>
#include "DynArray.h"

/**
 * Structure Texture
 * w: largeur
 * h: hauteur
 * texture : texture
 */
typedef struct {
	int w, h;
	SDL_Texture *texture;
}Texture;

/**
 * Structure police
 * font: police
 */
typedef struct {
	TTF_Font *font;
}Police;

/**
 * Structure Palette d'image
 * palette: Texture
 * clip: Coordonnées de chaques images
 * tilesize: taille des images
 */
typedef struct {
	Texture palette;
	ARRAY_CLIP clip;
	int tilesize;
}Tileset;

/**
 * Structure Animation
 * id: id de l'animation
 * currentX: Position X courante
 * currentY: Position Y courante
 * currentFram: Fram actuelle
 * clip: Position des images de l'animation
 */
typedef struct {
	int id;
	int currentX;
	int currentY;
	int currentFram;
	int nbFram;
	ARRAY_CLIP clip;

}Animation;


/**
 * Structure palette d'animations
 * palette: texture
 * nbAnimation: nombre d'animations
 * nbFramPAnim: nombre d'image par animation
 * animSize: taille des image
 * playFlag: Drapeau de lecture
 * animationArray: tableau d'animation
 */
typedef struct {
	Texture palette;
	int nbAnimations;
	int nbFramPAnim;
	int animSize;
	int nbAnim;
	unsigned int playFlag; //0x00000000 bit flag 8 animation a la fois
	Animation *animationArray; // tableau d'animation

}AnimationSet;

/**
 * Fonction d'initialisation de la SDL_image
 * @return Status du chargement
 */
int GRAPHIC_Init(void);

/**
 * Fonction libérant la mémoire alouée par SDL_image
 */
void GRAPHIC_Quit(void);

/*****************************************************************************************
 * Fonction Texture
 *****************************************************************************************/
/**
 * Fonction de chargement d'une texture
 * @param filename Fichier contenant la texture a charger
 * @param texture Structure où stoquer la texture
 */
void GRAPHIC_LoadTexture(char* filename, Texture* texture);

/**
 * Liberation de la texture
 * @param texture Structure a libérer
 */
void GRAPHIC_FreeTexture(Texture* texture);

/**
 * Application de la texture sur une position donnée avec largeur et hauteur
 * en paramètre
 * @param texture Texture a appliquer
 * @param posX Position X
 * @param posY Position Y
 * @param w Largeur
 * @param h Hauteur
 */
void GRAPHIC_ApplyTexture(Texture* texture, int posX, int posY, int w, int h);

/**
 * Application d'une texture avec la transparence
 * @param texture Texture a appliquer
 * @param posX Position X
 * @param posY Position Y
 * @param w Largeur
 * @param h Hauteur
 * @param alpha Valeur de transparence comprise entre 0 et 255
 */
void GRAPHIC_ApplyTextureAlpha(Texture* texture, int posX, int posY, int w, int h, int alpha);



/*****************************************************************************************
 * Fonction Text
 *****************************************************************************************/
/**
 * Chargement d'une police
 * @param filename Fichier de police
 * @param police Variable où conserver la police
 * @param size Taille de la police
 */
void GRAPHIC_LoadPolice(char* filename, Police *police, int size);

/**
 * Destruction de la variable
 * @param police Variable police
 */
void GRAPHIC_FreePolice(Police *police);

/**
 * Fonction affichage de texte sur l'ecran
 * @param police Police
 * @param posX Position X
 * @param posY Position Y
 * @param text Texte a afficher
 */
void GRAPHIC_Text(Police *police, int posX, int posY, char* text);

/**
 * Fonction affichage de texte sur l'ecran avec transparence
 * @param police Police
 * @param posX Position X
 * @param posY Position Y
 * @param alpha Valeur de transparence comprise entre 0 et 255
 * @param text Texte a afficher
 */
void GRAPHIC_TextAlpha(Police *police, int posX, int posY, int alpha, char* text);

/**
 * Affichage de texte Centré a l'ecran
 * @param police Police
 * @param posX Position X
 * @param posY Position Y
 * @param text Texte a afficher
 */
void GRAPHIC_TextCentered(Police *police, int posX, int posY, char* text);

/**
 * Affichage de texte Aligné a droite a l'ecran
 * @param police Police
 * @param posX Position X
 * @param posY Position Y
 * @param text Texte a afficher
 */
void GRAPHIC_TextRight(Police *police, int posX, int posY, char* text);

/**
 * Fonction affichage de texte Centrer sur l'ecran avec transparence
 * @param police Police
 * @param posX Position X
 * @param posY Position Y
 * @param alpha Valeur de transparence comprise entre 0 et 255
 * @param text Texte a afficher
 */
void GRAPHIC_TextCenteredAlpha(Police *police, int posX, int posY, int alpha, char* text);

/*****************************************************************************************
 * Fonction Tile
 *****************************************************************************************/

/**
 * Chargement palette d'image
 * @param filename Fichier
 * @param tileset Variable de conservation
 * @param tilesize Tailles d'une image dans la palette (16*16px)
 */
void GRAPHIC_LoadTile(char* filename, Tileset *tileset, int tilesize);

/**
 * Destruction variable
 * @param tileset Variable
 */
void GRAPHIC_FreeTile(Tileset *tileset);

/**
 * Application d'une image de la palette
 * @param tileset Variable
 * @param posX Position X sur la carte
 * @param posY Position Y sur la carte
 * @param id Id de l'image
 */
void GRAPHIC_ApplyTile(Tileset *tileset, int posX, int posY, int id);

/**
 * Application d'une image de la palette
 * @param tileset Variable
 * @param posX Position X sur la fenetre
 * @param posY Position Y sur la fenetre
 * @param id Id de l'image
 */
void GRAPHIC_ApplyTileRaw(Tileset *tileset, int posX, int posY, int id);


/*****************************************************************************************
 * Fonction Animation
 *****************************************************************************************/

/**
 * Chargement d'une palette d'animation
 * @param filename Fichier
 * @param animSet Variable
 * @param nbAnim Nombre d'animation
 * @param nbFramPAnim Nombre d'image par animation
 * @param animSize Taille des images
 */
void GRAPHIC_LoadAnimationSet(char* filename, AnimationSet* animSet, int nbAnim, int nbFramPAnim, int animSize);

/**
 * Destruction de la variable
 * @param animSet Variable animation
 */
void GRAPHIC_FreeAnimationSet(AnimationSet* animSet);

/**
 * Lecture d'une animation
 * @param animationSet Variable
 * @param posX Position X
 * @param posY Position Y
 * @param id Id de l'animation
 */
void GRAPHIC_PlayAnimation(AnimationSet *animationSet, int posX, int posY, int id);

/**
 * Affichage de l'animation
 * @param animationSet
 */
void GRAPHIC_DrawAnimation(AnimationSet *animationSet);

#endif /* GRAPHIC_H_ */
