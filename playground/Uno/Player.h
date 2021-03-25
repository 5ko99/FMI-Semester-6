#pragma once

#include "Card.h"


#define MAX_CARDS 10

class Player {
private :
    Card hand[MAX_CARDS];
    unsigned short curNumberOfCards;

public:
    Player();

    void drawCard(Card newCard);

    bool playCard(unsigned short cardToPlay, Card lastCard);

    void printHand();

    void moveCards();

    bool isWinner();

    bool canDraw();

    int getHandSize() const;


private:
    bool isValidCard();

    Card removeCard(short index);
};
