#ifndef LIB_CARDGAME_H
#define LIB_CARDGAME_H

 typedef struct
{
  int suite;
  int rank;
  int color;
} card;

typedef struct
{
  int No_Of_Decks;
  int No_Of_Cards;
  card *cards;
  int Next_Card;
  double cut_position;
  int is_past_cut;
} shoe;

int ReShuffle_Shoe (shoe * Pshoe, int verbose);
int Shuffle_Shoe   (shoe * Pshoe);
int Draw_Card      (shoe * Pshoe, card * Pcard);
int Print_Card     (card * Pcard);
int Print_Card2    (card * Pcard, int circle);
void Print_shoe    (shoe * Pshoe);
int Initialize_Shoe(shoe * Pshoe, int No_Of_Decks, int verbose);
void Destroy_Shoe  (shoe * Pshoe);
int Draw_Card      (shoe * Pshoe, card * Pcard);

/* ---      Function Descriptions  ---
Shuffle_Shoe       Shuffle the given shoe
Draw_Card	         Draw a card from the given deck
Print_Card         Print the given card (using full words)
Print_Card2        Print the given card (using the condensed format
Print_Shoe         Prints the given shoe
Initialize_Shoe    Initialize the shoe structure
Destroy_Shoe       Destroy the given shoe (release the resources)
Draw_Card          Draw card from a the given shoe
*/

/*
// Color
const int BLACK    = 0;
const int RED      = 1;
const char * Color[2] = {"BLACK","RED"};
const int black_or_red[4] = {1, 1, 0, 0};

// Suite
const int HEARTS   = 0; // red
const int DIAMONDS = 1; // red
const int CLUBS    = 2; // black
const int SPADES   = 3; // black
const char * Suite [4] = {"HEARTS", "DIAMONDS", "CLUBS", "SPADES"};
const char * Suite2[4] = {"H",      "D",        "C",     "S",    };

// rank
const int ACE      = 1;
const int TWO      = 2;
const int THREE    = 3;
const int FOUR     = 4;
const int FIVE     = 5;
const int SIX      = 6;
const int SEVEN    = 7;
const int EIGHT    = 8;
const int NINE     = 9;
const int TEN      = 10;
const int JACK     = 11;
const int QUEEN    = 12;
const int KING     = 13;
const char * Rank [14] = {"",      "ACE",   "TWO",   "THREE","FOUR", "FIVE",      
                          "SIX",   "SEVEN", "EIGHT", "NINE", "TEN",  "JACK", 
                          "QUEEN", "KING"};
const char * Rank2 [14] =  {"",  "A", "2",  "3", "4", "5", "6", "7",
                   			   "8", "9", "10", "J", "Q", "K"};
// Color
const int color[2] = {0, 1};
*/


// Color
#define BLACK         0
#define RED       1

// Suite
#define HEARTS    0 // red
#define DIAMONDS  1 // red
#define CLUBS     2 // black
#define SPADES    3 // black


// rank
#define ACE       1
#define TWO       2
#define THREE     3
#define FOUR      4
#define FIVE      5
#define SIX       6
#define SEVEN     7
#define EIGHT     8
#define NINE      9
#define TEN       10
#define JACK      11
#define QUEEN     12
#define KING      13

#endif