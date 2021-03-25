#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Game.h"

using std::cin;
using std::cout;
using std::endl;

Game::Game() {
    for (Player& player : players) {
        for (int j = 0; j < 3; j++) {
            player.drawCard(generateCard());
        }
    }
    currentCard = generateCard();
    isFPlRound = true;
}

Card Game::generateCard() {
    Card newCard;

    srand(time(NULL));
    newCard.number = rand() % 9 + 1;
    newCard.clr = static_cast<COLOR>(rand() % 4 + 1);
    return newCard;
}

void Game::printCurentCard() {
    cout << "\nCurrent card : " << currentCard.clr << "  " << currentCard.clr << endl;
}

void Game::printGame() {
    for (int i = 0; i < players[isFPlRound].getHandSize(); ++i) {
        cout << "\n " << i << " /";
        players[isFPlRound].printHand();
    }
    cout << "\n ";
}

int main() {
    std::cout << "Test\n";
    return 0;
}