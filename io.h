#ifndef IO_H
#define IO_H
#include<curses.h>
#include<menu.h>
#include"lib_blackjack.h"
int get_no_decks();
int get_no_players();
void update_players_hand(BJGame * game, int player_id);
void update_dealer_hand(BJPlayer * Pplayer, int first_hand);


#endif