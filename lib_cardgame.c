
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include"lib_cardgame.h"
//#include "lib_cardgame.h"
const char * Color[2] = {"BLACK","RED"};
const int black_or_red[4] = {1, 1, 0, 0};

const char * Suite [4] = {"HEARTS", "DIAMONDS", "CLUBS", "SPADES"};
const char * Suite2[4] = {"H",      "D",        "C",     "S",    };

const char * Rank [14] = {"",      "ACE",   "TWO",   "THREE","FOUR", "FIVE",      
                          "SIX",   "SEVEN", "EIGHT", "NINE", "TEN",  "JACK", 
                          "QUEEN", "KING"};
const char * Rank2 [14] =  {"",  "A", "2",  "3", "4", "5", "6", "7",
                           "8", "9", "10", "J", "Q", "K"};
// Color
const int color[2] = {0, 1};


int Shuffle_Shoe(shoe* Pshoe)
{
  int *assigned;
  int i;
  int current_card = 0;
  int s, r; // Suite and Rank loop counters
  int no_cards_assigned;
  int NODecks = Pshoe->No_Of_Decks;
  int NOCards = NODecks * 52;

  assigned = (int *) malloc(sizeof(int) * NOCards);
  no_cards_assigned = 0;

  for(i = 0; i < NOCards; i ++)
    {
      assigned[i] = 0;
    }

  for(i = 0; i < NODecks; i ++)
    {
    for(s = 0; s < 4 ; s += 1)
      {
      for(r = 1; r < 14; r += 1)
			{
	  		if(no_cards_assigned < NOCards)
	    	{
	      do {
					current_card = (rand() % NOCards);
	      		} while(assigned[current_card] == 1);
	      		assigned[current_card] = 1;
	      		no_cards_assigned += 1;
	      		Pshoe->cards[current_card].suite = s;
	      		Pshoe->cards[current_card].rank = r;
	      		Pshoe->cards[current_card].color = black_or_red[s];
	    }
		 }
     }
  }

  Pshoe->is_past_cut = 0;
  free(assigned);
  return 0;
}

int Draw_Card(shoe * Pshoe, card * Pcard)
{
  int current_card_up;
  current_card_up = Pshoe->Next_Card;
  Pshoe->Next_Card ++;
  (*Pcard) = Pshoe->cards[current_card_up];

  // Are there cards left in the shoe? return 0 for no, return 1 for yes.
  if(Pshoe->Next_Card > (Pshoe->No_Of_Cards - 1))
    return 0;
  else
    return 1;
}

int Print_Card(card * Pcard)
{

  printf("%s of %s", Rank[Pcard->rank], Suite[Pcard->suite]);
  return 0;
}

int Print_Card2(card * Pcard, int circle)
{
  int rank = Pcard->rank;
  int suite = Pcard->suite;
  if(circle == 1)
    {
      if((rank) != 10)
	printf("(%s%s)  ", Rank2[rank], Suite2[suite]);
      if((rank) == 10)
	printf("(%s%s) ", Rank2[rank], Suite2[suite]);
    }
  else
    {
      if((rank) != 10)
	printf("%s%s  ", Rank2[rank], Suite2[suite]);
      if((rank) == 10)
	printf("%s%s ", Rank2[rank], Suite2[suite]);
    }
  return 0;
}

void Print_Shoe(shoe *Pshoe)
{
  int i;
  for(i = 0; i < Pshoe->No_Of_Cards; i++)
    {
      Print_Card2(&Pshoe->cards[i], 1);
      printf("\n");
    }
}

int Initialize_Shoe(shoe * Pshoe, int NoDecks, int verbose)
{
  Pshoe->cut_position = 0;

  int NoCards = NoDecks * 52;
  Pshoe->No_Of_Cards = NoCards;
  Pshoe->No_Of_Decks = NoDecks;
  Pshoe->Next_Card = 0;

  Pshoe->cards =  (card*) malloc(sizeof(card) * NoCards);
  if(Pshoe->cards == 0)
    exit(1);
  if(verbose)
  printf("\nShuffling Shoe. . .");

  Shuffle_Shoe(Pshoe);

  if(verbose)
  printf("Done\n");

  srand(time(0));
  return 0;
}

void Destroy_Shoe(shoe *Pshoe)
{
  free(Pshoe->cards);
}
