#include "Unit.h"
#include<iostream>
#include<cmath>
Unit::Unit(unsigned int spend, unsigned short freq, bool type) : spend(spend),frequency(freq),type(type),distance(-1) {}

void Unit::print() const {
    std::string TYPE = type == NORMAL_BUY ? "Normal Buy" : "Special buy";
    std::string FREQUENCY;
    if (frequency == VERY_OFTEN) FREQUENCY = "Very often";
    if (frequency == OFTEN) FREQUENCY = "Often";
    if (frequency == SOMETIMES) FREQUENCY = "Sometimes";
    if (frequency == RARELY) FREQUENCY = "Rarely";
    printf("Type:%s, Spend:%d, Frequency:%s\n",TYPE.c_str(),spend,FREQUENCY.c_str());
}

void Unit::setEuclideanDistance(const Unit &other) {
    distance = sqrt((spend-other.spend)*(spend-other.spend)+(frequency-other.frequency)*(frequency-other.frequency));
}

bool Unit::operator<(const Unit &other) const {
    return (distance<other.distance);
}