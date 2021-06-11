#ifndef __PERSON_HH__
#define __PERSON_HH__ 

#include <string>
#include <vector>

class Vehicle;

//the class for the person
class Person {
    unsigned int ID; //unique identificator
    std::string name; //name
    std::vector<Vehicle*> ownedVehicles; //owned vehicles

    public:
    //a constructor with parameters - takes a name and an ID as arguments
    Person(const std::string& otherName, unsigned int otherID): name(otherName), ID(otherID) {}

    //selectors for the name, the ID and the vehicles of the person
    const std::string& getName() const; 
    unsigned int getID() const;
    const std::vector<Vehicle*>& getOwnedVehicles() const;

    void addVehicleOwnership(Vehicle* vehicle); //adds a vehicle to the vector of owned vehicles
    void removeVehicleOwnership(Vehicle* vehicle); //removes a vehicle from the vector of owned vehicles
    //void printOwnedVehicles(); //prints the owned vehicles a person has 

    friend std::ostream& operator<<(std::ostream& out,const Person& person); //writes info into a file 
};

#endif
