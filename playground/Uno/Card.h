#pragma once

enum class COLOR {
    unknown,
    red,
    blue,
    green,
    yellow
};

struct Card {
    unsigned short number;
    COLOR clr;

    Card();

    Card(COLOR newClr, unsigned short num);
};

