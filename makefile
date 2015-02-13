blackjack: main.c io.o lib_blackjack.o lib_cardgame.o 
	gcc -o blackjack main.c io.o lib_blackjack.o lib_cardgame.o

io.o: io.c lib_blackjack.o
	gcc -o io.o -c io.c lib_blackjack.o

lib_blackjack.o: lib_blackjack.c lib_cardgame.o
	gcc -o lib_blackjack.o -c lib_blackjack.c lib_cardgame.o

lib_cardgame.o: lib_cardgame.c
	gcc -o lib_cardgame.o -c lib_cardgame.c

clean:
	rm *.o