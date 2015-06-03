#include "Pause.h"
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
Instance* Pause_Instance(void)
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

static SDL_Event event;
static int clk=0;
static int fps = (1/30)*1000;
static int alpha = 255;

static Police Gpolice;
static Texture noir;
static Texture PauseScreen;

static void Init()
{
	GRAPHIC_LoadTexture("./Assets/Textures/black.png", &noir);
	GRAPHIC_LoadPolice("./Assets/Fonts/font.ttf", &Gpolice, 24);
	GRAPHIC_LoadTexture("./Assets/Textures/PauseScreen.png", &PauseScreen);

	GRAPHIC_ApplyTextureAlpha(&noir, 0, 0,
			Game_GetVariables()->Window_W,
			Game_GetVariables()->Window_H , 127);

}
static void CleanUp()
{
	GRAPHIC_FreeTexture(&noir);
	GRAPHIC_FreePolice(&Gpolice);
	GRAPHIC_FreeTexture(&PauseScreen);
}
static void Pause()
{

}
static void Resume()
{

}
static void HandleEvent()
{
	SDL_PollEvent(&event);
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
				Game_PopState();
				break;
			case SDLK_q:
				Game_Quit();
				break;
			}
			break;
		}
	}
}
static void Update()
{
	clk = SDL_GetTicks();
	if( (fps) > SDL_GetTicks() - clk)
		SDL_Delay(fps - (SDL_GetTicks() - clk));
}
static void Draw()
{
	GRAPHIC_ApplyTexture(&PauseScreen, 0, 0,
			Game_GetVariables()->Window_W,
			Game_GetVariables()->Window_H);

	alpha -= 5;
	if(alpha < -255) alpha = 255;
	GRAPHIC_TextCenteredAlpha(&Gpolice, 304+337, 160+20/*54*/, abs(alpha),"Pause");
	GRAPHIC_TextCenteredAlpha(&Gpolice, 304+337, 160/*+54*/+20+40, abs(alpha),"Espace pour reprendre");

	SDL_RenderPresent(Game_GetVariables()->renderer);
}
