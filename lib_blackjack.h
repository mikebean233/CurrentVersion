#ifndef LIB_BLACKJACK_H
#define LIB_BLACKJACK_H
#include<stdio.h>
#include"lib_cardgame.h"

typedef struct
{
  card cards[21];
  int no_of_cards;
  int is_soft;
  int is_blackjack;
  int count;
} BJHand;

typedef struct{
  card dealer_up_card;
  double running_count;
  double true_count;
  int options[6];
} Play_Sit;

typedef struct
{
  BJHand Hand;
  int Current_Bet;
  int Std_Bet;
  int Balance;  /* How much money do you have left */
  int (*strat_func)(void *, void *, void *);   /* The Strategy function for the player */
  int is_dealer;   /* Is the player a dealer? (0 no, 1 yes) */
  int next_action;
  int player_no;
  Play_Sit situation;
  int count_type;
  int result;
  char* result_string;
  int in_game;
} BJPlayer;

typedef struct{
  int dealer_hit_soft_17;
  int allow_dd_on[14];      // What cards are the are the player allowed to double down on                                                       
  int allow_spit_aftekr_dd;  // Allow spliting after doubling down                                                                               
  int offer_insurance;
  int allow_surrender;
} BJGameRules;

typedef struct
{
  int no_of_players;
  int no_of_decks;
  shoe Shoe;
  BJPlayer Dealer;
  BJPlayer *Pplayer;
  BJGameRules game_rules;
} BJGame;
/*
// player action flags
const int HIT         = 0;
const int STAND       = 1;
const int STAY        = 1;
const int SPLIT       = 2;
const int DOUBLE_DOWN = 3;
const int SURRENDER   = 4;
const int INSURANCE   = 5;
const char * options[6] = {"HIT", "STAY", "SPLIT", "DOUBLE DOWN", "SURRENDER", "INSURANCE"};
*/

#define HIT             0
#define STAND           1
#define STAY            1
#define SPLIT           2
#define DOUBLE_DOWN     3
#define SURRENDER       4
#define INSURANCE       5





/*
// card counting type flags
const int CARD_COUNTING_NONE = 0;
const int CARD_COUNTING_HILOW = 1;

// game result flags
const int LOSE           = 0;
const int LOST					= 0;
const int PUSH           = 1;
const int PUSHED				= 1;
const int WIN            = 2;
const int WON					= 2;
*/

// card counting type flags
#define CARD_COUNTING_NONE   0;
#define CARD_COUNTING_HILOW  1;

// game result flags
#define LOSE            0;
#define LOST            0;
#define PUSH            1;
#define PUSHED          1;
#define WIN             2;
#define WON             2;




int BJHand_Initialize   (BJHand * Phand);
int BJHand_Add_Card     (BJHand * Phand, card * pcard);
int BJHand_Count        (BJHand * Phand);
int Is_BJ_BJHand        (BJHand * Phand);
int Print_BJHand        (BJHand * Phand);
int BJHand_Can_Split    (BJHand * Phand);
int BJHand_Is_Soft      (BJHand * Phand);
void Deal_To_Player     (BJPlayer *Pplayer, shoe *Pshoe);
void Reshuffle_Shoe     (shoe *Pshoe, int ask_for_split);
void update_player_Sit  (BJPlayer * Pplayer, BJPlayer * Pdealer);
//void update_dealer_hand(BJPlayer*Pplayer, ,0);
void handle_decision    (int decision, BJPlayer * Pplayer, BJPlayer * Pdealer, shoe * PShoe);

void Print_Player_Hand  (BJPlayer * Pplayer, int player_no);
void Deal_First_Round   (BJGame * game);
void Deal_Second_Round  (BJGame * game);
void Finish_Player_Hands(BJGame * game);
void Finish_Dealers_Hand(BJGame * game);
void Find_Game_Results  (BJGame * game);
void Print_Dealer_First_Hand(BJHand * Phand);

#endif