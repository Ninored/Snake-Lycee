/*
 * GamePattern.h
 *
 *  Created on: 21 avr. 2015
 *      Author: Ulysse
 */

#ifndef GAMEPATTERN_H_
#define GAMEPATTERN_H_

#include <stdlib.h>

typedef void (*FonctVoid)(void);

typedef struct {
	FonctVoid Init;
	FonctVoid CleanUp;

	FonctVoid Pause;
	FonctVoid Resume;

	FonctVoid HandleEvent;
	FonctVoid Update;
	FonctVoid Draw;

} Instance;

#endif /* GAMEPATTERN_H_ */
