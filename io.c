#include "io.h"
//#include <time.h>
#include <stdio.h>
#include "lib_blackjack.h"

int get_no_decks()
{
  int tmp;
  printf("How many decks would you like to play with?");
  scanf("%d", &tmp);
  return tmp;
  //game->no_of_decks = tmp;
}

int get_no_players()
{
  int tmp;
  printf("How many players?");
  scanf("%d", &tmp);
  return tmp;
}

void update_dealer_hand(BJPlayer * Pplayer, int first_hand)
{
  printf("\n\n\n");
  printf("------- DEALERS HAND -------\n");
  if(first_hand)
    Print_Dealer_First_Hand(&Pplayer->Hand);
  else
    Print_BJHand(&Pplayer->Hand);
  printf("\n-----------------------------\n");
}