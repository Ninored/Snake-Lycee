
#include "Play.h"
#include "GameManager.h"
#include "Graphic.h"
#include "TilesID.h"
#include "Snake.h"
#include "Map.h"
#include "SplashScreenPlay.h"

static void Init();
static void CleanUp();
static void Pause();
static void Resume();
static void HandleEvent();
static void Update();
static void Draw();

// Declaration de l'instance.
static Instance instance;
Instance* Play_Instance(void)
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
static Texture background;
static Tileset tileset;
static Serpent serpent;
static int clk = 0;  // variable temps ecoulé entre chaque images
static int ms = 50; // vitesse de deplacement en miliseconde

void Init()
{
	SDL_RenderClear(Game_GetVariables()->renderer);
	GRAPHIC_LoadTile("./Assets/Play/tileset.png",&tileset, 16);
	GRAPHIC_LoadTexture("./Assets/Play/Play_Background.jpg", &background);
	SERPENT_Init(&serpent);
	MAP_Init();

	Game_PushState(SplashPlay_Instance());

}

void CleanUp()
{
	GRAPHIC_FreeTile(&tileset);
	GRAPHIC_FreeTexture(&background);
}

void Pause()
{

}

void Resume()
{

}

void HandleEvent()
{


	SDL_PollEvent(&event); // recupération des evenements
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
					SERPENT_ChangeDirection(&serpent, NORD);
					break;

				case SDLK_DOWN:
					SERPENT_ChangeDirection(&serpent, SUD);
					break;

				case SDLK_LEFT:
					SERPENT_ChangeDirection(&serpent, OEST);
					break;

				case SDLK_RIGHT:
					SERPENT_ChangeDirection(&serpent, EST);
					break;

					// Pour le debug
				case SDLK_t:
					SERPENT_Grow(&serpent);
					break;
				case SDLK_r:
					MAP_GenerateRandomeItem();
					break;
				}
				break;
			}

}

void Update()
{
	clk = SDL_GetTicks();
	if( (ms) > SDL_GetTicks() - clk)
		SDL_Delay(ms - (SDL_GetTicks() - clk));

	MAP_GenerateRandomeItem();


	SERPENT_Avancer(&serpent);


	//Gestion colision Avec mure pome et autre
	SERPENT_GetColision(&serpent);
}

void Draw()
{

	SDL_RenderClear(Game_GetVariables()->renderer);

	GRAPHIC_ApplyTexture(&background, 0, 0, Game_GetVariables()->Window_W, Game_GetVariables()->Window_H);
	MAP_Draw();

	SERPENT_Draw(&serpent, &tileset);

	SDL_RenderPresent(Game_GetVariables()->renderer);
//	SDL_UpdateWindowSurface(Game_GetVariables()->window);
}