#include "Score.h"
#include <stdio.h>



static int scorePomme;
static int scoreCerise;
static char buffer[16];

void SCORE_Reset(void)
{
	scorePomme = 0;
	scoreCerise = 0;
}

void SCORE_Add(enum ITEM item)
{
	switch(item)
	{
	case POMME:
		scorePomme++;
		break;
	case CERISE:
		scoreCerise++;
		break;
	}
}

char* SCORE_Get(enum ITEM item)
{
	switch(item)
	{
	case POMME:
		sprintf(buffer, "%d", scorePomme);
		break;
	case CERISE:
		sprintf(buffer, "%d", scoreCerise);
		break;
	}
	return buffer;
}
char* SCORE_GetTotal(void)
{
	int total = scorePomme + 10*scoreCerise;
	sprintf(buffer, "%d", total);
	return buffer;
}
