#pragma once
#include "Vehicle.cpp"

class Garage
{
    Vehicle **data = nullptr; // Array that stores Vehicle pointers
    std::size_t capacity = 0; // Size of array
    std::size_t occupied = 0; // Space occupied by vehicles

    void copyFrom(const Garage &other); //Helper copy function, used in Copy constructor and operator =

public:

    Garage() = default;

    /*
        Creates an array of nullptr with capacity - size
        @param size the capacity of the array
        @exception if new fails to allocate memory
    */
    Garage(std::size_t size);

    /*
        Copy constructor 
        @param other class to be copied 
    */
    Garage(const Garage &other);

    /*
        Deletes the old Garage and calls copyFrom func
        @param other Garage to be copied
        @note if copyFrom func fails the old data is lost
    */
    Garage &operator=(const Garage &other);

    /*
        Inserts Vehicle address into the array of pointers
        If a vehicle occupies n slots it is stored
        in n slots of the array
        @param v Vehicle to be inserted
        @exception if there are no free slots left or 
        not enough space
        @exception if the registration number already exists
        in the array
    */
    void insert(Vehicle &v);

    /*
        Sets wanted Vehicle`s slots to nullptr and moves to
        their place the last occupied elements of the array
        @param registration searches for the vehicle by reg
        number
    */
    void erase(const char *registration);

    /*
        Acces to the Vehicle at this position
        @param pos position to be accessed
        @exception if pos has invalid value
    */
    const Vehicle &at(std::size_t pos) const;

    /*
        Acces to the Vehicle at this position
        @param pos position to be accessed
        @note due to performance the index is not checked if it is in bounds
    */
    const Vehicle &operator[](std::size_t pos) const;

    /*
        Checks if the Garage has occupied = 0
    */
    bool empty() const;

    /*
        Returns number of occupied slots by Vehicles
        @return param occupied
    */
    std::size_t size() const;

    /*
        Sets all pointers in the array to nullptr
        Sests occupied param to 0 but does not change
        the capacity
    */
    void clear();

    /*
        Finds by registration number a Vehicle in the array
        if there is no match returns nullptr
        @return pointer to Vehicle
    */
    const Vehicle *find(const char *registration) const;
    
    ~Garage();
};