#include "SplashScreenGameOver.h"
#include "GameManager.h"
#include "Graphic.h"
#include "Play.h"
#include "TilesID.h"
#include "Map.h"
#include "Score.h"

static void Init();
static void CleanUp();
static void Pause();
static void Resume();
static void HandleEvent();
static void Update();
static void Draw();

// Declaration de l'instance.
static Instance instance;
Instance* SplashGameOver_Instance(void)
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


//Static Variables
static SDL_Event event;
static Police police;
static Police Gpolice;
static Texture scoreBoard;
static Texture noir;
static Tileset tileset;
static int clk=0;
static int fps = (1/60)*1000;
static int alpha = 255;

void Init()
{
	GRAPHIC_LoadTexture("./Assets/Textures/ScoreBoard.png", &scoreBoard);
	GRAPHIC_LoadTexture("./Assets/Textures/black.png", &noir);
	GRAPHIC_LoadPolice("./Assets/Fonts/font.ttf", &police, 16);
	GRAPHIC_LoadPolice("./Assets/Fonts/font.ttf", &Gpolice, 24);
	GRAPHIC_LoadTile("./Assets/Tilesets/tileset.png", &tileset, 16);


	GRAPHIC_ApplyTextureAlpha(&noir, 0, 0,
			Game_GetVariables()->Window_W,
			Game_GetVariables()->Window_H , 127);
}
void CleanUp()
{
	GRAPHIC_FreeTexture(&scoreBoard);
	GRAPHIC_FreeTexture(&noir);
	GRAPHIC_FreePolice(&police);
	GRAPHIC_FreePolice(&Gpolice);
	GRAPHIC_FreeTile(&tileset);
}
void Pause()
{

}
void Resume()
{

}
void HandleEvent()
{
	if(SDL_PollEvent(&event) == 1)
	{
		switch (event.type) {
		case SDL_QUIT:		// fermeture de la fenetre
			Game_Quit();
			break;

		case SDL_KEYDOWN:	// Touche pressé
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE: 	// ESC
				Game_Quit();
				break;
			case SDLK_SPACE:	// Espace
				Game_Quit();
				break;
			case SDLK_r:
				Game_ChangeState(Play_Instance());
				break;
			}
			break;
		}
	}
}
void Update()
{
	clk = SDL_GetTicks();
	if( (fps) > SDL_GetTicks() - clk)
		SDL_Delay(fps - (SDL_GetTicks() - clk));

}
void Draw()
{

	GRAPHIC_ApplyTexture(&scoreBoard, 0, 0,
			Game_GetVariables()->Window_W,
			Game_GetVariables()->Window_H);


	GRAPHIC_TextCentered(&police, (int)((Game_GetVariables()->Window_W)/2), (240+16*2), "Score");

	//GRAPHIC_ApplyTileRaw(&tileset, 528, 336, TILE_POMME);
	//GRAPHIC_Text(&police, 528+200, 332, SCORE_Get(POMME));

	GRAPHIC_ApplyTileRaw(&tileset, 532+4, 340+4, TILE_POMME);
	GRAPHIC_TextRight(&police, 747, 340, SCORE_Get(POMME));

	GRAPHIC_ApplyTileRaw(&tileset, 532+4, 340+32+4, TILE_CERISE);
	GRAPHIC_TextRight(&police, 747, 371, SCORE_Get(CERISE));

	GRAPHIC_Text(&police, 532+2, 402, "TOTAL:");
	GRAPHIC_TextRight(&police, 747, 402, SCORE_GetTotal());

	alpha -= 5;
	if(alpha < -255) alpha = 255;
	GRAPHIC_TextCenteredAlpha(&Gpolice, 640, 544+60-27, abs(alpha),"Espace pour Quitter");
	GRAPHIC_TextCenteredAlpha(&Gpolice, 640, 544+60, abs(alpha),"R pour rejouer");

	SDL_RenderPresent(Game_GetVariables()->renderer);
	SDL_UpdateWindowSurface(Game_GetVariables()->window);
}
