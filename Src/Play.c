
#include "Play.h"
#include "GameManager.h"
#include "Graphic.h"
#include "TilesID.h"
#include "Snake.h"
#include "Map.h"
#include "SplashScreenPlay.h"
#include "Score.h"
#include "Pause.h"

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
static Police font;
static Tileset tileset;
static AnimationSet animationset;
static Serpent serpent;
static int clk = 0;  // variable temps ecoulé entre chaque images
static int ms = 50; // vitesse de deplacement en miliseconde

void Init()
{
	SDL_RenderClear(Game_GetVariables()->renderer);
	GRAPHIC_LoadTile("./Assets/Tilesets/tileset.png",&tileset, 16);
	GRAPHIC_LoadTexture("./Assets/Textures/Play_Background.jpg", &background);
	GRAPHIC_LoadPolice("./Assets/Fonts/font.ttf", &font, 16);
	GRAPHIC_LoadAnimationSet("./Assets/Animations/pommeAnimation.png", &animationset, 4, 4, 48);
	SERPENT_Init(&serpent);
	MAP_Init();

	Game_PushState(SplashPlay_Instance());
}

void CleanUp()
{
	GRAPHIC_FreeTile(&tileset);
	GRAPHIC_FreeTexture(&background);
	GRAPHIC_FreePolice(&font);
	GRAPHIC_FreeAnimationSet(&animationset);
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
					Game_PushState(Pause_Instance());
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
				}
				break;
			}

}

void Update()
{

	clk = SDL_GetTicks();
	if( (ms) > SDL_GetTicks() - clk)
		SDL_Delay(ms - (SDL_GetTicks() - clk));



	// Génération d'item
	MAP_GenerateRandomeItem();

	// Faire avancer le serpent
	SERPENT_Avancer(&serpent);


	//Gestion colision Avec mure pome et autre
	SERPENT_GetColision(&serpent);
}

void Draw()
{

	SDL_RenderClear(Game_GetVariables()->renderer);

	GRAPHIC_ApplyTexture(&background, 0, 0, Game_GetVariables()->Window_W, Game_GetVariables()->Window_H);

	//GRAPHIC_Text(&font, 22, 0, SCORE_Get());
	GRAPHIC_Text(&font, 24, 4, SCORE_Get(POMME));
	GRAPHIC_Text(&font, 105, 4, SCORE_Get(CERISE));

	unsigned int i;
	for(i = 0; i < SERPENT_GetLives(&serpent); i++)
	{
		GRAPHIC_ApplyTileRaw(&tileset, 168 + i*(16+5) , 8, TILE_COEUR);
	}

	MAP_Draw();

	SERPENT_Draw(&serpent, &tileset); // Serpent
	GRAPHIC_DrawAnimation(&animationset); // Les animations si nécessaire

	SDL_RenderPresent(Game_GetVariables()->renderer);
	SDL_UpdateWindowSurface(Game_GetVariables()->window);
}
