#include "SplashScreenPlay.h"
#include "GameManager.h"
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
Instance* SplashPlay_Instance(void)
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


// Static Variables
static Texture un;
static Texture deux;
static Texture trois;
static Texture background;
static Texture noir;
static int number;
static int clk;

void Init()
{
	GRAPHIC_LoadTexture("./Assets/Textures/1.png", &un);
	GRAPHIC_LoadTexture("./Assets/Textures/2.png", &deux);
	GRAPHIC_LoadTexture("./Assets/Textures/3.png", &trois);
	GRAPHIC_LoadTexture("./Assets/Textures/black.png", &noir);
	GRAPHIC_LoadTexture("./Assets/Textures/Play_Background.jpg", &background);
	number = 3;
	clk = 0;
}
void CleanUp()
{
	GRAPHIC_FreeTexture(&un);
	GRAPHIC_FreeTexture(&deux);
	GRAPHIC_FreeTexture(&trois);
	GRAPHIC_FreeTexture(&noir);
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
	number--;
}
void Update()
{
	if(number < 3 )
	{
		clk = SDL_GetTicks();
		if( (1000) > SDL_GetTicks() - clk)
			SDL_Delay(1000 - (SDL_GetTicks() - clk));
	}
	if(number <= 0)
		Game_PopState();
}
void Draw()
{
	SDL_RenderClear(Game_GetVariables()->renderer);

	GRAPHIC_ApplyTexture(&background, 0, 0,
			Game_GetVariables()->Window_W,
			Game_GetVariables()->Window_H);

	GRAPHIC_ApplyTextureAlpha(&noir, 0, 0,
			Game_GetVariables()->Window_W,
			Game_GetVariables()->Window_H , 127);

	switch(number)
	{
	case 1: GRAPHIC_ApplyTexture(&un, 0, 0,
			Game_GetVariables()->Window_W,
			Game_GetVariables()->Window_H);
		break;
	case 2: GRAPHIC_ApplyTexture(&deux, 0, 0,
			Game_GetVariables()->Window_W,
			Game_GetVariables()->Window_H);
		break;
	case 3: GRAPHIC_ApplyTexture(&trois, 0, 0,
			Game_GetVariables()->Window_W,
			Game_GetVariables()->Window_H);
		break;
	}


	SDL_RenderPresent(Game_GetVariables()->renderer);
	SDL_UpdateWindowSurface(Game_GetVariables()->window);
}
