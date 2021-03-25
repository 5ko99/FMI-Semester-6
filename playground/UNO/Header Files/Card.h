#pragma once
#include <iostream>

#define DEFAULT_CARD_NUMBER 14

enum class COLOR {
	UNKNOWN = -1,
	RED,
	BLUE,
	GREEN,
	YELLOW
};

class Card{
private:
	COLOR color;
	unsigned short number;

public:
	Card(COLOR color = COLOR::UNKNOWN, unsigned short number=DEFAULT_CARD_NUMBER);
	Card(const Card& other);
	Card& operator=(const Card& other);
	bool operator==(const Card& other) const;
	bool operator!=(const Card& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Card& card);

public:
    const COLOR& getColor() const;
	unsigned short getNumber() const;

public:
	void generateRandom();
	void changeColor(int _color);
};