
#ifndef GARAGE_H
#define GARAGE_H


#include "Vehicle.h"
/*FOR ME:
my_size - the square space of a garage
std::size() - the number of cars in a garage

Vehicle
spaceTaken = square space for each car
vehicles.length() - the number of objects in the array vehicles
*/
class Garage{
    /// this is the capacity of the garage
    std::size_t my_size;
    Vehicle** vehicles;
public:

    Garage();
    /*Garage& operator=(const Garage& other);
    Garage(const Garage& other);*/

    Garage(std::size_t size);
    void insert(Vehicle& v);
    void erase(const char* registration);
    const Vehicle& at(std::size_t pos) const;
    const Vehicle& operator[](std::size_t pos) const;
    bool empty() const;

    /// this returns the number of Vehicles in the garage
    std::size_t size() const;
    void clear();
    const Vehicle* find(const char* registration) const;

    ~Garage();
};
#endif // GARAGE_H
