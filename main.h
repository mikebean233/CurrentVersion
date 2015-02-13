#ifndef BLACKJACK_H
#define BLACKJACK_H

#include"lib_blackjack.h"


int Strategy_0(void * p1, void * p2, void * p3);
int Strategy_1(void * p1, void * p2, void * p3);
int Strategy_2(void * p1, void * p2, void * p3);
int Strategy_3(void * p1, void * p2, void * p3);
int Strategy_4(void * p1, void * p2, void * p3);

void BJGame_Initialize(BJGame * Game);
#endif