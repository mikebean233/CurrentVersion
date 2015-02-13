#include"lib_blackjack.h"
#include"io.h"

const char * options[6] = {"HIT", "STAY", "SPLIT", "DOUBLE DOWN", "SURRENDER", "INSURANCE"};
const char * result[3] = {"LOSES", "PUSHES", "WINS"};



void Finish_Dealers_Hand(BJGame * game)
{
	
	 update_dealer_hand(&game->Dealer,0);
	while(game->Dealer.Hand.count <= 17)
	{
	   if(game->Dealer.Hand.is_soft && (game->Dealer.Hand.count == 17))
	   {
	      if(game->game_rules.dealer_hit_soft_17)
	      { 
           printf("\nDealer takes another card\n");
           Deal_To_Player(&game->Dealer, &game->Shoe);   
           update_dealer_hand(&game->Dealer,0);
	      }
	   }
	   else
	   {
	      if(game->Dealer.Hand.count < 17)
        {  
           printf("\nDealer takes another card\n");
           Deal_To_Player(&game->Dealer, &game->Shoe);   
           update_dealer_hand(&game->Dealer,0);
        }	      
	      else
	         break;
	   }
	}
   if(game->Dealer.Hand.count > 21)
      printf("\nDealer has busted\n");
}

void  update_player_Sit(BJPlayer * Pplayer, BJPlayer * Pdealer)
{

  // determine what options the player has,  evaluate one at a time.     \
                                                                          
  // HIT                                                                 \
                                                                          
  if(BJHand_Count(&Pplayer->Hand) < 21)
    Pplayer->situation.options[HIT] = 1;
  else
    Pplayer->situation.options[HIT] = 0;
  // STAY                                                                \
                                                                          
  Pplayer->situation.options[STAY] = 1;
  // SPLIT                                                               \
                                                                          
  if(BJHand_Can_Split(&Pplayer->Hand))
    Pplayer->situation.options[SPLIT] = 1;
  // DOUBLE_DOWN                                                         \
                                                                          
  Pplayer->situation.options[DOUBLE_DOWN] = 1;
  // SURRENDER                                                           \
                                                                          
  Pplayer->situation.options[SURRENDER] = 1;
  // INSURANCE                                                           \
                                                                          
  Pplayer->situation.options[INSURANCE] = 1;

  Pplayer->situation.dealer_up_card = Pdealer->Hand.cards[0];
}

void Print_Player_Hand(BJPlayer * Pplayer, int player_no)
{
  printf("\n\n\n");
  printf("------- PLAYER(%d)S HAND -------\n", Pplayer->player_no);
  Print_BJHand(&Pplayer->Hand);
  if(BJHand_Is_Soft(&Pplayer->Hand))
    {
      printf(" or (%d)", (BJHand_Count(&Pplayer->Hand) - 10 ));

    }
  printf("\n---------------------------------\n");
}



void handle_decision(int decision, BJPlayer * Pplayer, BJPlayer * Pdealer, shoe * PShoe)
{
  switch(decision)
    {
    case 0: //HIT                                                                                    
      {
        int new_decision;
        Deal_To_Player(Pplayer, PShoe);
        update_player_Sit(Pplayer, Pdealer);
        Print_Player_Hand(Pplayer, Pplayer->player_no);
        if((BJHand_Count(&Pplayer->Hand)) > 21)
          {
            printf("\nPlayer %d has BUSTED\n", Pplayer->player_no);
            break;
          }
        new_decision = (*Pplayer->strat_func)(Pplayer, 0,0);
	printf("Player %d Chooses to %s   ", Pplayer->player_no, options[new_decision]);

        handle_decision(new_decision, Pplayer, Pdealer, PShoe);
        break;
      }
    case 1: //STAY                                                                                   
      {
        break;
      }
    case 2: // SPLIT                                                                                 
      break;
    case 3: // DOUBLE_DOWN                                                                           
      break;
    case 4: // SURRENDER                                                                             
      break;
    case 5: // INSURANCE                                                                             
      break;
    }
}

int BJHand_Add_Card(BJHand * Phand, card * pcard)
{
  Phand->cards[Phand->no_of_cards].rank = pcard->rank;
  Phand->cards[Phand->no_of_cards].suite = pcard->suite;
  Phand->cards[Phand->no_of_cards].color = pcard->color;
  Phand->no_of_cards ++;

  return 0;
}

int BJHand_Initialize(BJHand * Phand)
{
  int i;
  for(i = 0; i < 21; i ++)
    Phand->cards[i].suite = -1;
  Phand->cards[i].rank = -1;
  Phand->cards[i].color = -1;
  Phand->no_of_cards = 0;
  return 0;
}


void Reshuffle_Shoe(shoe *Pshoe, int ask_for_split)
{
  if (ask_for_split)
    {
      printf("\n\nwhere would you like to split the shoe?\n (enter a decimal between .25 and .75)");
      scanf("%lf", &Pshoe->cut_position);
      printf("");
    }
  else
    {
      Pshoe->cut_position = .5;
    }
  Shuffle_Shoe(Pshoe);
}

void Deal_To_Player(BJPlayer *Pplayer, shoe *Pshoe)
{
  card Tcard;

  if(Draw_Card(Pshoe, &Tcard) == 0)
    Reshuffle_Shoe(Pshoe, 1);

  BJHand_Add_Card(&(Pplayer->Hand), &Tcard);
  Pplayer->Hand.count = BJHand_Count(&Pplayer->Hand);
  if(Pplayer->Hand.count > 21)
     Pplayer->in_game = 0;
  else
     Pplayer->in_game = 1;
}

int Print_BJHand(BJHand * Phand)
{
  int Hand_Count;
  int i;
  for(i = 0; i < Phand->no_of_cards; i++)
    {
      Print_Card2(&Phand->cards[i], 0);
    }
  Hand_Count = BJHand_Count(Phand);
  printf("(");
  printf("%d", Hand_Count);
  printf(") ");
  if(Is_BJ_BJHand(Phand) )
    printf("BLACKJACK");

  return 0;
}

void Print_Dealer_First_Hand(BJHand * Phand)
{
  Print_Card2(&Phand->cards[0], 0);
  printf("XX");
}

int Is_BJ_BJHand(BJHand * Phand)
{
  if(Phand->no_of_cards == 2 && BJHand_Count(Phand) == 21)
    return 1;
  else
    return 0;
}

int BJHand_Can_Split(BJHand * Phand)
{
  int no_of_cards = Phand->no_of_cards;
  int i;
  int no_hits[14];
  int can_split = 0;

  for(i = 0; i < 14; i ++)
    no_hits[i] = 0;

  for(i = 1; i < no_of_cards + 1; i ++)
    {
      no_hits[Phand->cards[i].rank] ++;
      if(no_hits[Phand->cards[i].rank] > 2)
	can_split = 1;
    }
  return can_split;
}

int BJHand_Is_Soft(BJHand * Phand)
{
  BJHand_Count(Phand);
  return Phand->is_soft;
}

int BJHand_Count(BJHand * Phand)
{
  int no_of_aces;
  int running_total;
  int i;
  int is_soft = 0;
  running_total = 0;
  no_of_aces = 0;
  i = 0;


// if there is only one card, then the value of the hand is that of                              
// the card (ace counted as 11 of course).                                                       
if(Phand->no_of_cards == 1)
  {
    if(Phand->cards[0].rank == ACE)
      {
        return 11;
      }
    else
      {
	if(Phand->cards[0].rank < JACK)
	  return Phand->cards[0].rank;
	else
	  return 10;
      }
  }
// figure out the count if there is more then one card.                                          
for(i = 0; i < Phand->no_of_cards; i ++)
  {
    if(Phand->cards[i].rank == ACE)
      {
        running_total ++;
        no_of_aces ++;
      }
    else
      {
	if(Phand->cards[i].rank >= TEN)
	  {
	    running_total += 10;
	  }
	else
	  {
	    running_total += Phand->cards[i].rank;
	  }
      }
  }
// determine if the aces will be counted as a one or eleven.                                     
for(i = 0; i < no_of_aces; i++)
  {
    if ((running_total + 10) <= 21)
      {
	running_total += 10;
	is_soft = 1;
      }
  }
Phand->is_soft = is_soft;
  if(Phand->no_of_cards == 2 && running_total == 21)
    Phand->is_blackjack = 1;
  else
    Phand->is_blackjack = 0;

return running_total;
}




void Deal_First_Round   (BJGame * game)
{
int i;	

 // Deal first card to every player, then to the dealer
      if(game->Shoe.Next_Card / game->Shoe.No_Of_Cards > game->Shoe.cut_position)
	    {
	      Reshuffle_Shoe(&(game->Shoe), 1);
	    }
      for(i = 0; i < game->no_of_players; i ++)
      {
	  Deal_To_Player(&(game->Pplayer[i]), &(game->Shoe));
	  }
      Deal_To_Player(&(game->Dealer), &(game->Shoe));
} 

void Deal_Second_Round  (BJGame * game)
{
	int i;
  //Deal 2nd card to every player, then to the dealer (hidden)
      for(i=0; i < game->no_of_players; i++)
	  {
	  Deal_To_Player(&(game->Pplayer[i]), &(game->Shoe));
	  }
      Deal_To_Player(&(game->Dealer), &(game->Shoe));
}

void Finish_Player_Hands(BJGame * game)
{
      int i;
      
      // Give the player options, get their decision, then act on the decision
      int player_decision;
      update_dealer_hand(&(game->Dealer), 1);

      for(i=0; i < game->no_of_players; i++)
	{
	  update_player_Sit(&(game->Pplayer[i]), &(game->Dealer));
	  Print_Player_Hand(&(game->Pplayer[i]), i);

	  // Receive the players action from the players strategy function
	  player_decision = (*(game->Pplayer[i].strat_func))(&(game->Pplayer[i]), 0, 0);
	  
	  printf("Player %d Chooses to %s   ", i, options[player_decision]);
	  handle_decision(player_decision, &(game->Pplayer[i]), &(game->Dealer), &(game->Shoe));
	  	}
}


void Find_Game_Results  (BJGame * game)
{
   int i;
   for(i=0;i<game->no_of_players;i++)
   {
   	if(game->Pplayer[i].in_game && game->Pplayer[i].Hand.count <= 21)
   	{
       if(game->Dealer.Hand.is_blackjack)
          {
             if(game->Pplayer[i].Hand.is_blackjack)
             {
                game->Pplayer[i].result = PUSH;
             }
             else
             {
                game->Pplayer[i].result = LOSE;
              }
          }
          else
          {
          if(game->Dealer.Hand.count <= 21)
          { 
             if(game->Pplayer[i].Hand.count > game->Dealer.Hand.count)
	              game->Pplayer[i].result = WIN;
	  
	           if(game->Pplayer[i].Hand.count < game->Dealer.Hand.count)
	              game->Pplayer[i].result = LOSE;
	  
	           if(game->Pplayer[i].Hand.count == game->Dealer.Hand.count)
	              game->Pplayer[i].result = PUSH;
	        }
	        else
	        {
	             game->Pplayer[i].result = WIN;
	        }
	     }
	  }
	  else
	 game->Pplayer[i].result = LOSE; 
   game->Pplayer[i].result_string = (char*) result[game->Pplayer[i].result];
   }  
}
