#include "SplashScreenGameOver.h"
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
static Texture scoreBoard;
static Texture noir;

void Init()
{
	GRAPHIC_LoadTexture("./Assets/SplashScreenGameOver/ScoreBoard.png", &scoreBoard);
	GRAPHIC_LoadTexture("./Assets/SplashScreenGameOver/black.png", &noir);
	GRAPHIC_LoadPolice("./Assets/SplashScreenGameOver/font.ttf", &police, 16);


	GRAPHIC_ApplyTextureAlpha(&noir, 0, 0,
			Game_GetVariables()->Window_W,
			Game_GetVariables()->Window_H , 127);
}
void CleanUp()
{
	GRAPHIC_FreeTexture(&scoreBoard);
	GRAPHIC_FreeTexture(&noir);
	GRAPHIC_FreePolice(&police);
}
void Pause()
{

}
void Resume()
{

}
void HandleEvent()
{
	SDL_WaitEvent(&event);
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
		}
		break;
	}
}
void Update()
{

}
void Draw()
{

	GRAPHIC_ApplyTexture(&scoreBoard, 0, 0,
			Game_GetVariables()->Window_W,
			Game_GetVariables()->Window_H);


	GRAPHIC_TextCentered(&police, (int)((Game_GetVariables()->Window_W)/2), (240+16*2), "Score");

	SDL_RenderPresent(Game_GetVariables()->renderer);
}
