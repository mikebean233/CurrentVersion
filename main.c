#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include"main.h"
#include"lib_blackjack.h"
#include"lib_cardgame.h"
#include"io.h"

int main()
{
  srand(time(0));
  int Play_Again = 1;
  BJGame Game;
  int i, tmp;
  card Drawn_Card;
  
    while(Play_Again)
    {
    Game.no_of_decks = get_no_decks();
    Game.no_of_players = get_no_players();
    
    BJGame_Initialize(&Game);
    /*  --------------------  TEMPORARY --------------*/
    // give the user control of player 0.
    Game.Pplayer[0].strat_func = &Strategy_0;
    printf("\n   ---- player strategies  ---- \n");
    printf("Player 1: User Controlled\n");
    /*  ----------------------------------------------*/
     
    for(i = 0; i < Game.no_of_players; ++i)
      printf("Player %i: Strategy no 1 (hit on everthing under 15)\n", i);

    printf("\n");
    Deal_First_Round(&Game);
    Deal_Second_Round(&Game);    
    Finish_Player_Hands(&Game);
    Finish_Dealers_Hand(&Game);
    Find_Game_Results(&Game);
    

      for(i = 1; i < Game.no_of_players; i++)
	{
	  printf("\nPlayer %d %s.\n",i, Game.Pplayer[i].result_string);
	}
      Destroy_Shoe(&(Game.Shoe));
      free(Game.Pplayer);

      printf("\nPlay Again?(1: yes,  0: no)");
      scanf("%d", &Play_Again);
      }
  return 0;
}


// This strategy asks the user what to do
int Strategy_0(void * p1, void * p2, void * p3)
{
  BJPlayer *Pplayer = p1;
  int fail = 1;
  int input;
  while(fail)
  {
	  printf("\n\nEnter action for player %d:\n", Pplayer->player_no);
	  if(Pplayer->situation.options[HIT])
		  printf("Hit         ( 0 )\n");

	  if(Pplayer->situation.options[STAND])
		  printf("Stay        ( 1 )\n");

	  if(Pplayer->situation.options[SPLIT])
		  printf("Split       ( 2 )\n");

	  if(Pplayer->situation.options[DOUBLE_DOWN])
		  printf("Double Down ( 3 )\n");

	  if(Pplayer->situation.options[SURRENDER])
		  printf("Surrender   ( 4 )\n");

	  if(Pplayer->situation.options[INSURANCE])
		  printf("Insurance   ( 5 )\n");
	  scanf("%d", &input);
	  if(Pplayer->situation.options[input] == 1 && (input >= 0 && input <= 4))
	  {
		  fail = 0;
		  return input;
	  }
	  else
	  {
		  printf("Sorry, that is not a valid option\n");
		  fail = 1;

	  }
   }
    return 0;
}

int Strategy_1(void * p1, void * p2, void * p3)
{
  // hit on everything under 15
  BJPlayer *Pplayer = p1;
  if(Pplayer->situation.options[HIT] == 1)
    {
      if(BJHand_Count(&Pplayer->Hand) < 15)
	return HIT;
      else 
	return STAY;
    }
  return STAY;
}

int Strategy_2(void * p1, void * p2, void * p3)
{
    return 0;
}

int Strategy_3(void * p1, void * p2, void * p3)
{
    return 0;
}

void BJGame_Initialize(BJGame * Game)
{
  int i;

  Initialize_Shoe(&Game->Shoe, Game->no_of_decks, 1);
  Reshuffle_Shoe(&Game->Shoe, 1);

  // Initialize players (and dealer)                                      
  Game->Pplayer = malloc(sizeof(BJPlayer) * Game->no_of_players);

  // set properties for all the players
  for(i = 0; i < Game->no_of_players; i ++)
    {
      BJHand_Initialize(&(Game->Pplayer[i].Hand));
      Game->Pplayer[i].player_no = i;
      Game->Pplayer[i].is_dealer = 0;
      Game->Pplayer[i].strat_func = &Strategy_1;
      Game->Pplayer[i].count_type = CARD_COUNTING_HILOW;
    }
  BJHand_Initialize(&(Game->Dealer.Hand));
}
