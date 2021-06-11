#ifndef Person_hpp
#define Person_hpp

#include "../Vehicle/Vehicle.hpp"
#include <iostream>
#include <string>
#include <vector>

class Vehicle;
class Person {
private:
    std::string name;
    unsigned int uid;
    std::vector<Vehicle*> vehiArr;
public:
    Person(const std::string& newName, const unsigned int& newUid);
    
    void acquire(Vehicle& vehi);
    void release(const Registration& reg);
    void releaseAll();
    bool owns(const Registration& reg);
    
    const std::string& getName() const;
    const unsigned int& getUid() const;
    const bool hasVehicles() const;
    
    void print() const;
    void printWithVehicles() const;
};


#endif
