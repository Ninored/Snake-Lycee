/*
 * menu.c
 *
 *  Created on: 21 avr. 2015
 *      Author: Ulysse
 */

#include "Menu.h"
#include "Play.h"
#include <stdio.h>

#include "GamePattern.h"
#include "GameManager.h"

#include <SDL2/SDL.h>
#include "Graphic.h"

static void Init();
static void CleanUp();
static void Pause();
static void Resume();
static void HandleEvent();
static void Update();
static void Draw();

// Declaration de l'instance.
static Instance instance;
Instance* MENU_Instance(void)
{
		instance.Init = Init;
		instance.CleanUp = CleanUp;
		instance.Pause = Pause;
		instance.Resume = Resume;
		instance.HandleEvent = HandleEvent;
		instance.Update = Update;
		instance.Draw = Draw;

	return &instance;
}

// Variables Propre au fichier
static SDL_Event event;
static int selector = 0;
static int clk = 0;
static int fps = (1/60) * 1000;
static int alpha = 255;
static Police font;
static Texture background;

// Fonctions de l'instance
void Init()
{
	SDL_RenderClear(Game_GetVariables()->renderer);
	GRAPHIC_LoadPolice("./Assets/Menu/font.ttf", &font, 22);
	GRAPHIC_LoadTexture("./Assets/Menu/Menu_Background_Button.jpg",&background);

	// push state splash screen

}

void CleanUp()
{
	GRAPHIC_FreeTexture(&background);
	GRAPHIC_FreePolice(&font);
}

void Pause()
{
}
void Resume()
{
}

void HandleEvent()
{
	// Gestion de l'evenement
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:		// fermeture de la fenetre
			Game_Quit();
			break;

		case SDL_KEYDOWN:	// Touche pressé
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE: 	// ESC
				Game_Quit();
				break;

			case SDLK_UP:
				selector--;
				if(selector <=-1) selector = 1;
				alpha = 255;
				break;
			case SDLK_DOWN:
				selector++;
				if(selector >= 2) selector = 0;
				alpha = 255;
				break;
			case SDLK_RETURN:
				if(selector == 0) Game_ChangeState(Play_Instance());
				if(selector == 1) Game_Quit();
			}
			break;
		}
	}
}
void Update()
{
	// clock
	clk = SDL_GetTicks();
	if( (fps) > SDL_GetTicks() - clk)
		SDL_Delay(fps - (SDL_GetTicks() - clk));
}void Draw()
{
	SDL_RenderClear(Game_GetVariables()->renderer);

	GRAPHIC_ApplyTexture(&background, 0, 0, Game_GetVariables()->Window_W, Game_GetVariables()->Window_H);

	if(selector == 0)
	{
		alpha -= 5;
		if(alpha < -255) alpha = 255;
		GRAPHIC_TextCenteredAlpha(&font, 640, 388, abs(alpha),"PLAY");
	}
	else
	{
		GRAPHIC_TextCentered(&font, 640, 388, "PLAY");
	}

	if(selector == 1)
	{
		alpha -= 5;
		if(alpha < -255) alpha = 255;
		GRAPHIC_TextCenteredAlpha(&font, 640, 544, abs(alpha),"EXIT");
	}
	else
	{
		GRAPHIC_TextCentered(&font, 640, 544,"EXIT");
	}


	SDL_RenderPresent(Game_GetVariables()->renderer);
	SDL_UpdateWindowSurface(Game_GetVariables()->window);
}
