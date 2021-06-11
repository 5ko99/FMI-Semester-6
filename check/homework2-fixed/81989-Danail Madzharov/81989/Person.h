#ifndef PERSON_H
#define PERSON_H
#include "Registration.h"
using namespace std;
#include <vector>

class Person {
    string name;
    unsigned int id;
    vector<Registration*> ownedCars;
    
    public:
    Person(string newName, unsigned int newId);
    string getName();
    unsigned int getId();
    vector<Registration*> getOwnedCars();
    void removeCar(Registration*);
    void addCar(Registration*);
};

#endif
