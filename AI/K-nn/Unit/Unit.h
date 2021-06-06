#pragma once
#define NORMAL_BUY 0
#define SPECIAL_BUY 1

#define VERY_OFTEN 3
#define OFTEN 2
#define SOMETIMES 1
#define RARELY 0
struct Unit {
    unsigned int spend;
    unsigned short frequency;
    bool type;
    double distance;
    explicit Unit(unsigned int spend = 0,unsigned short freq = 0, bool type = NORMAL_BUY);
    void print() const;
    void setEuclideanDistance(const Unit& other);
    bool operator<(const Unit& other) const;
};