#ifndef IS_SOFT_C
#define IS_SOFT_C

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"blackjack.h"

int main()
{
  srand(time(0));
  BJHand hand;
  shoe   BJShoe;
  int i;
  card tmp_card;
  int no_of_decks = 12;
  const char* y_or_n[] = {"NO", "YES"};
  Initialize_Shoe(&BJShoe, no_of_decks, 1);
  BJHand_Initialize(&hand);
  
  for(i = 1; i < ((no_of_decks * 52) / 2) - 1; i ++)
    {
      if(!Draw_Card(&BJShoe, &tmp_card))
	break;
      BJHand_Add_Card(&hand, &tmp_card);

      Draw_Card(&BJShoe, &tmp_card);
      BJHand_Add_Card(&hand, &tmp_card);
    
      printf("\n");
      Print_BJHand(&hand);
      printf("  is soft . . . %s",  y_or_n[BJHand_Is_Soft(&hand)]  );
      
      //printf("issoft ? (%d)\n", BJHand_Is_Soft(&hand));
      BJHand_Initialize(&hand);
    } 
  Destroy_Shoe(&BJShoe);
      return 0;
}
#endif