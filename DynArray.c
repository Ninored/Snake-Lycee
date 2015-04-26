#include "DynArray.h"

/**
 * Fonction d'initialisation de la structure de coordonnée
 * @param a Structur de coordonnées
 */
void ARRAY_CLIP_INIT(ARRAY_CLIP *a)
{
	a->size  = 1; // initialisation de la taille.
	a->used  = 0; // initialisation des case utilisé.
	a->array = (SDL_Rect*)malloc(sizeof(SDL_Rect)); // mise en place d'une case
}

/**
 * Fonction permettant l'ajout d'une coordonnée dans la structure donnée en paramètre
 * @param a	Structur de coordonnées
 * @param _x Coordonnée X
 * @param _y Coordonnée Y
 * @param _w Largeur du carré
 * @param _h Hauteur du carré
 */
void ARRAY_CLIP_ADD(ARRAY_CLIP *a, int _x, int _y, int _w, int _h)
{
	if(a->size == a->used)	// si taille du tableau = taille utilisé
	{
		a->size++;	// augmante la taille
		a->array = (SDL_Rect*)realloc(a->array, a->size * sizeof(SDL_Rect)); // réalou la mémoire
	}

	SDL_Rect tmp;

	tmp.x = _x;
	tmp.y = _y;
	tmp.w = _w;
	tmp.h = _h;

	a->array[a->used++] = tmp;
}

/**
 * Suppréssion de la structure donnée en paramètre
 * @param a Structure de coordonnées
 */
void ARRAY_CLIP_DESTROY(ARRAY_CLIP *a)
{
	free(a->array); // libération du tableau
	a->array = NULL; // pointeur sur NULL
	a->size = a->used = 0; // mise a 0 des variables
}
