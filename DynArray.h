#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H
/**
 * @file DynArray.h
 * @brief Conteneur dynamique
 *
 * Ce fichier contient tout les daclaration nécessaire
 * a l'utilisation des conteneur dynamique utile dans le projet
 */

#include <SDL2/SDL.h>
#include <stdlib.h>

/**
 * @struct ARRAY_CLIP
 * @brief Structur coordonnées carré
 *
 * Structure contenant des coordonnées de carré
 * Cette structure est utiliser pour mettre en mémoire
 * les coordonnées de chacun des tiles (images ou portions d'image)
 * dans une palette définit
 */
typedef struct {

	SDL_Rect *array;	/*!< Coordonnée du carré */
	unsigned int used; 	/*!< Nombre d'objet dans le conteneur */
	unsigned int size;	/*!< Taille du conteneur */
} ARRAY_CLIP;

void ARRAY_CLIP_INIT(ARRAY_CLIP *a);
void ARRAY_CLIP_ADD(ARRAY_CLIP *a, int _x, int _y, int _w, int _h);
void ARRAY_CLIP_DESTROY(ARRAY_CLIP *a);

#endif // DYN_ARRAY_H
