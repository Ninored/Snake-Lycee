/*
 * main.c
 *
 *  Created on: 21 avr. 2015
 *      Author: Ulysse
 */

#include <stdlib.h>
#include <stdio.h>

#include "GameManager.h"
#include "Menu.h"

int main( int argc, char* argv[])
{

	printf("Démarage\n");

	Game_Init();
	Game_ChangeState(MENU_Instance());

	while(Game_Running())
	{
		Game_HandleEvent();
		Game_Update();
		Game_Draw();
	}

	Game_CleanUp();
	return 0;
}
