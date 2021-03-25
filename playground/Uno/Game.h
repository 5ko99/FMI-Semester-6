#include "Player.h"


class Game {
private:
    //int numberOfPlayers; //=2
    Player players[2];
    Card currentCard;
    bool isFPlRound;

public :
    Game(); // add cards for players & first card
    Game(unsigned short startingHand); //generate startingHands

    Card generateCard();

    bool nextTurn();

    void printGame();

    void printCurentCard();


};


/*
Current card :  red  2 


Your hand:    (Indexs->)    0    1    2
             (clr ->)     blue  red green
           (numbers ->)      4    2    1


 Current card :  red  2  //current Idea 

   0. /red 3 /
   1. /yellow 4/

*/