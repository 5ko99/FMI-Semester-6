#ifndef GARAGE_H
#define GARAGE_H

#include "vehicle.hpp"

class Garage
{
private:
    Vehicle ** garage;  //!< stores a pointer to an array with Vehicle pointers
    size_t vehicles;    //!< stores the count of the vehicles currently in the garage
    size_t usedSpace;   //!< stores the used space in the garage
    size_t capacity;    //!< stores the number of park spaces availiable in the garage

    /**
     * Private function
     * Finds the index of the vehicle with the given registration
     * 
     * @param registration - used to find the vehicle in the garage
     * @return Returns the index of the vehicle in the garage if it's found, and -1 if there's not such vehice
     */
    int findIndex(const char* registration) const;

    ///deletes the current content and copy the new one
    void copy(Vehicle** garage, size_t vehicles, size_t usedSpace, size_t capacity);

public:
    ///Constructor taking the capacity of the array;
    Garage(std::size_t size);

    ///Constructor copying the content of the other garage
    Garage(const Garage& other);

    //copies the content of the other garage
    Garage& operator=(const Garage& other);

    //Destructor
    ~Garage();

    /**
     * Inserts vehicle in the garage
     * 
     * @param v the vehicle that should be added to the garage
     * @throw std::invalid argument if the vehicle is already in the garage
     * @throw std::length error if there's not enough space in the garage for the vehicle
     */
    void insert(Vehicle& v);

    /**
     * Erases vehicle from the garage
     * 
     * @param registration - the registration of the vehicle we want to erase
     */
    void erase(const char* registration);
    
    /**
     * Access vehicle in the garage
     * Main use should be to iterate through the array that garage stores
     * 
     * @param pos is the position of the vehicle we want to access
     * @throw std::out_of_range if the given position is invalis
     */
    const Vehicle& at(std::size_t pos) const;

    /**
     * Access vehicle in the garage
     * 
     * Doesn't validate the position
     * @param pos is the position od the vehicle we want to access
     */
    const Vehicle& operator[](std::size_t pos) const;

    ///returns true if the garage is empty
    bool empty() const;

    ///Returns how many vehicles are curently in the garage
    std::size_t size() const;

    ///Removes all vehicles
    void clear();

    /**
     * Finds vehicle in the garage
     * Uses findIndex(const char*) const function
     * 
     * @see int findIndex(const char* registration) const
     * @param registration - the registration of the vehicle we want to find
     * @return const pointer to the vehicle with the given registration
     */
    const Vehicle* find(const char* registration) const;
};

#endif