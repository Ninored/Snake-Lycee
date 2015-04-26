/*
 * StateContainer.c
 *
 *  Created on: 21 avr. 2015
 *      Author: Ulysse
 */

#include "StateContainer.h"
#include <stdlib.h>


void SV_Init(StateVector *sv)
{
	sv->size = 1;
	sv->used = 0;
	sv->vector = (Instance**)malloc(sizeof(Instance*));
}
void SV_Destroy(StateVector *sv)
{
	free(sv->vector);
	sv->vector = NULL;
	sv->size = 0;
	sv->used = 0;
}

void SV_PushState(StateVector *sv, Instance *instance)
{
	if(sv->size == sv->used)
	{
		sv->size++;
		sv->vector = (Instance**)realloc(sv->vector, sv->size * sizeof(Instance*));
	}

	sv->vector[sv->used++] = instance;

}
void SV_PopState(StateVector *sv)
{
	Instance **tmp  = (Instance**)malloc((sv->size - 1) * sizeof(Instance*));

	unsigned int i = 0;
	for(i = 0; i < sv->used - 1; i++ )
	{
		tmp[i] = sv->vector[i];
	}
	free(sv->vector);
	sv->vector = tmp;
}
