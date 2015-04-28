/*
 * GameManager.c
 *
 *  Created on: 21 avr. 2015
 *      Author: Ulysse
 */

#include "GameManager.h"
#include "StateContainer.h"
#include <stdio.h>
#include <stdio.h>

#include "Graphic.h"


static StateVector stateVec;
static GameVariables gameVariables;
bool running;

GameVariables* Game_GetVariables(void)
{
	return &gameVariables;
}

void Game_Init()
{
	SV_Init(&stateVec); // Initialisation du vecteur state

	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		printf("[ERROR]\tError while initializing SDL : %s \n", SDL_GetError());
		exit(-1);
	}
	printf("[INFO]\tSDL initialized\n");

	// Initialisation de la SDL_image
	if(GRAPHIC_Init() == -1)
		exit(-1);

	//Creation de la fenetre
	gameVariables.Window_H = 16 * MAP_H;  //720
	gameVariables.Window_W = 16 * MAP_W;  //1280
	gameVariables.window =
			SDL_CreateWindow(
					"SNAKE",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					gameVariables.Window_W,
					gameVariables.Window_H,
					SDL_WINDOW_SHOWN);
	if(gameVariables.window == NULL)
	{
		printf("[ERROR]\tError while creating window: %s \n", SDL_GetError());
		exit(-1);
	}

	//Creation du contexte de rendu
	gameVariables.renderer =
			SDL_CreateRenderer(
					gameVariables.window,
					-1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(gameVariables.renderer == NULL)
	{
		printf("[ERROR]\tError while generating Renderer context: %s \n", SDL_GetError());
		exit(-1);
	}

	running = true;
}
void Game_CleanUp()
{
	unsigned int i = 0;
	for(i = 1; i < stateVec.used; i++)
	{
		stateVec.vector[i]->CleanUp();
		SV_PopState(&stateVec);
	}

	SV_Destroy(&stateVec);
	SDL_DestroyRenderer(gameVariables.renderer);
	SDL_DestroyWindow(gameVariables.window);

	GRAPHIC_Quit();
	SDL_Quit();

	printf("[INFO]\tProgram Exit\n");

}
void Game_Quit()
{
	running = false;
}

bool Game_Running()
{
	return running;
}

void Game_ChangeState(Instance *instance)
{
	if(stateVec.used != 0)
	{
		stateVec.vector[stateVec.used - 1]->CleanUp();
		SV_PopState(&stateVec);
	}

	SV_PushState(&stateVec, instance);
	stateVec.vector[stateVec.used - 1]->Init();
}
void Game_PushState(Instance *instance)
{
	if(stateVec.used != 0)
	{
		stateVec.vector[stateVec.used - 1]->Pause();
	}

	SV_PushState(&stateVec, instance);
	stateVec.vector[stateVec.used - 1]->Init();
}
void Game_PopState()
{
	if(stateVec.used != 0)
	{
		stateVec.vector[stateVec.used - 1]->CleanUp();
		SV_PopState(&stateVec);
	}

	if(stateVec.used !=0)
	{
		stateVec.vector[stateVec.used - 1]->Resume();
	}
}

void Game_HandleEvent()
{
	stateVec.vector[stateVec.used - 1]->HandleEvent();
}
void Game_Update()
{
	stateVec.vector[stateVec.used - 1]->Update();
}
void Game_Draw()
{
	stateVec.vector[stateVec.used - 1]->Draw();
}
