#ifndef SCORE_H_
#define SCORE_H_

#include "Map.h"

void SCORE_Reset(void);
void SCORE_Add(enum ITEM item);
char *SCORE_Get(enum ITEM item);
char *SCORE_GetTotal(void);


#endif /* SCORE_H_ */
