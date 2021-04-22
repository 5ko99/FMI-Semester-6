#pragma once
#include "Vehicle.h"

class Garage
{
private:
    ///How much is the size of the garage.
    ///AKA how many spaces there are left
    std::size_t memSize = 0;

    ///Array of pointers to vehicles. That way we don't accidentally remove a vehicle
    Vehicle **parkingSpaces;


    ///How many are the free spaces.
    std::size_t free = 0;

    ///How many are the occupied spaces.
    std::size_t occupied = 0;

public:
    ///Creates a new garage with given size.
    Garage(std::size_t size);

    ///Adds a vehicle to the garage.
    ///If there is no space throws exception.
    ///If there is a vehicle with the same registration number throws exception.
    ///If there is not enough memory throws exception.
    void insert(Vehicle &v);

    ///Removes the vehicle with given registration number.
    ///If there is not one it does nothing.
    ///After removal it is acceptable to change the order of the
    ///vehicles in the array (aka not do a left shift)
    void erase(const char *registration);

    ///Access to the element at position pos.
    ///If there is none throw std::out_of_range
    const Vehicle &at(std::size_t pos) const;

    ///Access to the element at position pos.
    ///Function doesn't do a check if pos is valid.
    const Vehicle &operator[](std::size_t pos) const;

    ///Check if the garage is empty.
    bool empty() const;

    ///Returns the number of elements(vehicles) in the garage.
    std::size_t size() const;

    ///Clear the garage of vehicles.
    ///Doesn't change the size of the garage.
    void clear();

    ///Finds and returns the vehicle with given registration number in the garage.
    ///If there is none return nullptr.
    const Vehicle *find(const char *registration) const;

};