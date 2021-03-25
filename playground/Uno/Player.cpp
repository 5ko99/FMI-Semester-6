#include "Player.h"

Player::Player() : curNumberOfCards(3) {}

Player::Player(unsigned short startingHand, const Card *cards) {
    //if(startingHand is valid? )
    curNumberOfCards = startingHand;
    for (int i = 0; i < startingHand; ++i) {
        hand[i].clr = cards[i].clr;
        hand[i].number = cards[i].number;
    }
}

bool Player::canDraw() {
    return (curNumberOfCards < MAX_CARDS);
}

void Player::drawCard(Card newCard) {
    if (canDraw()) {
        hand[curNumberOfCards].clr = newCard.clr;
        hand[curNumberOfCards++].number = newCard.number; //DRY !!!
        return;
    }
}

Card Player::removeCard(short index) {
    Card removedCard;

    if (index < curNumberOfCards && index >= 0) {
        removedCard.number = hand[index].number;
        removedCard.clr = hand[index].clr;

        for (int i = index + 1; i < curNumberOfCards; ++i) {
            hand[i - 1].clr = hand[i].clr;
            hand[i - 1].number = hand[i].number;
        }
        curNumberOfCards--;
        return removedCard;
    }
    //else
    removedCard.clr = unknown;
    removedCard.number = 10;
    return removedCard;
    //throw error?
}

bool Player::isWinner() {
    return (curNumberOfCards == 0);
}
