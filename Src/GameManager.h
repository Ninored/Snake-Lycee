#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "GamePattern.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

#define MAP_W 80	// taille en tile
#define MAP_H 45 // taille en tile


typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	int Window_W;
	int Window_H;
	SDL_Surface *icon;
}GameVariables;

GameVariables* Game_GetVariables(void);

void Game_Init();
void Game_CleanUp();
void Game_Quit();
bool Game_Running();

void Game_ChangeState(Instance *instance);
void Game_PushState(Instance *instance);
void Game_PopState();

void Game_HandleEvent();
void Game_Update();
void Game_Draw();

#endif /* GAMEMANAGER_H_ */
