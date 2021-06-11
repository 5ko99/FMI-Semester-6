#include "Person.h"
using namespace std;

Person::Person(string newName, unsigned int newId) : name(newName), id(newId) {}

string Person::getName() {
    return this->name;
}

unsigned int Person::getId() {
    return this->id;
}

vector<Registration*> Person::getOwnedCars() {
    return this->ownedCars;
}

void Person::removeCar(Registration* car) {
    int counter = 0;
    bool found = false;
    for (Registration* current : this->ownedCars)
    {
        if(current == car) {
            found = true;
            break;
        }
        ++counter;
    }
    if(found) {
        this->ownedCars.erase(this->ownedCars.begin() + counter);
    }
}

void Person::addCar(Registration* car) {

    for (Registration* current : this->ownedCars)
    {
        if (current == car)
        {
            return;
        }
    }

    this->ownedCars.push_back(car);
}
