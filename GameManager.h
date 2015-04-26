/*
 * GameManager.h
 *
 *  Created on: 21 avr. 2015
 *      Author: Ulysse
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "GamePattern.h"
#include <stdbool.h>
#include <SDL2/SDL.h>


typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	int Window_W;
	int Window_H;
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
