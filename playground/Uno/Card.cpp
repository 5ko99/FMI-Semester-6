#include <iostream>
#include "Card.h"

/*
    unknown,
    red,
    blue,
    green,
    yellow
    */
Card::Card() {
    clr = COLOR::unknown;
    number = 10;
}

Card::Card(COLOR newClr, unsigned short num) : clr(newClr), number(num) {
    if (num < 1 || num > 9) {
        number = 10;
        std::cerr << "Invalid card number!\n";
    }
    if (clr == COLOR::unknown) {
        std::cerr << "Unknown card color!\n";
    }
}
