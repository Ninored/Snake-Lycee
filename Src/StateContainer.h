/*
 * StateContainer.h
 *
 *  Created on: 21 avr. 2015
 *      Author: Ulysse
 */

#ifndef STATECONTAINER_H_
#define STATECONTAINER_H_

#include "GamePattern.h"


typedef struct
{
	Instance **vector;
	unsigned int used;
	unsigned int size;

} StateVector;

void SV_Init(StateVector *sv);
void SV_Destroy(StateVector *sv);

void SV_PushState(StateVector *sv, Instance *instance);
void SV_PopState(StateVector *sv);


#endif /* STATECONTAINER_H_ */
