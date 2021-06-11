#include "Vehicle.h"
using namespace std;

Vehicle::Vehicle(Registration* newRegistration, string newDescription) : 
registrationNumber(newRegistration), description(newDescription), owner(nullptr) {};

Registration* Vehicle::getRegistrationNumber(){
    return this->registrationNumber;
}

Person* Vehicle::getOwner() {
    return this->owner;
}

string Vehicle::getDescription() {
    return this->description;
}

void Vehicle::setOwner(Person* person) {
    if(this->owner != nullptr){
        this->owner->removeCar(this->registrationNumber);
    }
    
    this->owner = person;
}
