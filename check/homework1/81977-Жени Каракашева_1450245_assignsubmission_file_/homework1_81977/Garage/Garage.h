#ifndef __GARAGE_HH__
#define __GARAGE_HH__
#include <iostream>
#include "../Vehicle/Vehicle.h"

//Notes on the class for the Garage:
//1: The description of the problem for homework has said that the interface shouldn't be changed
//   but we are allowed to have whatever we need in the private part - that's why I added the
//   counter and the last index
//2: The last index is needed since it is much less effective to go through an array with the size of
//   capcity(especially if it is a huge number like 20 000) while we have like only 2-3 vehicles
//
//3: I have put some messages around the code(for example in the find() method) since they would be used by the user
//   and in my opinion, it would be better if they know what is going on

//the class for Garage
class Garage {
    std::size_t capacity; //the capacity of the garage
    Vehicle** vehicles; //an array of pointers to data of type pointer to Vehicle for the vehicles

    std::size_t counter; //a counter for how many vehicles we have in the garage
    std::size_t lastIndex; //an index which helps us run search through the vehicle array quicker

    public:
    Garage(std::size_t otherCapacity); //a constructor which uses the capacity
    Garage(const Garage& other); //a copy constructor
    Garage& operator =(const Garage& other); //operator =
    ~Garage(); //destructor

    void insert(Vehicle& v); //the insert() method - adds a vehicle in the garage
    void erase(const char* registration); //the erase() method - removes a vehicle from the garage
    const Vehicle& at(std::size_t pos) const; //the at() method - gives access to the element at pos
    const Vehicle& operator[](std::size_t pos) const; //operator[] - gives access to the element at pos
    bool empty() const; //the empty() method - checks if the garage is empty
    std::size_t size() const; //the size() method - returns the number of vehicles in the garage
    void clear(); //the clear() method - empties the garage
    const Vehicle* find(const char* registration) const; //the find() method - finds a vehicle in the garage
};

#endif