#include "Vehicle.h"

// Vehicle::Vehicle() 
//     : owner(nullptr), regNumber("")
// {
// }

Vehicle::Vehicle(const Registration& registrationN, const string& carDescript) 
    : regNumber(registrationN), carDescription(carDescript)//, owner(newOwner)
{ 
}

string Vehicle::getDescr() const {
    return carDescription;
}

string Vehicle::getRegistrationNumb() const {
    return regNumber.getRegNumber();
}

bool Vehicle::isOwned() const {
    return owner != nullptr;
}

Person* Vehicle::getOwner() const {
    return owner;
}

void Vehicle::setOwner(Person& otherOwner) {
    if (isOwned()) {
        owner->removeVehicle(regNumber.getRegNumber());
    } 
    
    owner = &otherOwner;
    otherOwner.addVehicle(*this);
}

void Vehicle::removeOwner() {
    if (owner) {
        owner->removeVehicle(regNumber.getRegNumber());
        owner = nullptr;
    }

    else {
        cout << "This car has no owner!" << endl;
    }
}

 void Vehicle::printCommand(std::ostream& out) const {
    out << "VEHICLE " << getRegistrationNumb() << " " << carDescription << endl;
    
    // Cannot reuse isOwned command, because ->
    // -> the object has type qualifiers that are not compatible with the member function
    if (owner != nullptr) { 
        out << "ACQUIRE " << owner->getID() << " " << getRegistrationNumb() << endl;
    }
}

void Vehicle::printEverything(std::ostream& out) const {
    out << getRegistrationNumb() << " with description: " << getDescr() << endl;

    if (owner != nullptr) {
        out << "Is owned by: " << owner->getName() << " with ID: " << owner->getID() << endl;
    }
}

// TODO: not sure these two

bool Vehicle::operator==(const Registration& registrationNumbr) const {
    return regNumber == registrationNumbr;
}

bool Vehicle::operator==(const string& registrationNumbr) const {
    return regNumber == registrationNumbr;

}

bool Vehicle::operator==(const Vehicle& otherVehicle) const {
    return this->regNumber == otherVehicle.regNumber;
}

std::ostream& operator<<(std::ostream& out, const Vehicle& newVehcile) {
    out << newVehcile.getRegistrationNumb() << " with description: " << newVehcile.getDescr();
    return out;
}
