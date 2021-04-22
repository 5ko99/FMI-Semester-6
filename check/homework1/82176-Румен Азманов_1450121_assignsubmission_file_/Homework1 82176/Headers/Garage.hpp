#ifndef GARAGE_HPP
#define GARAGE_HPP

#include <assert.h>

#include <cstring>
#include <iostream>

#include "MyString.hpp"
#include "Vehicle.hpp"

class Garage {
   private:
    // Vehicle order starts from 1, not from 0!!!
    std::size_t sizeOfGarage;
    std::size_t occupiedOfGarage;
    std::size_t occupiedIndex;
    Vehicle** vehicles;

   public:
    //! Constructor
    Garage(std::size_t size);

    //! Copy constructor
    Garage(const Garage& other);

    //! Copy assignment operator
    Garage& operator=(const Garage& other);

    //! Insert a vehicle in the garage
    void insert(Vehicle& v);

    //! Remove a vehicle from the garage
    void erase(const char* registration);

    //! Vehicle index access
    const Vehicle& at(std::size_t pos) const;

    //! Vehicle index access with [] operartor
    const Vehicle& operator[](std::size_t pos) const;

    //! Empty garage verification
    bool empty() const;

    //! Number of vehicles in garage
    std::size_t size() const;

    //! Clear the garage
    void clear();

    //! Search a vehicle by registration
    const Vehicle* find(const char* registration) const;

    //! Destructor
    ~Garage();
};

#endif