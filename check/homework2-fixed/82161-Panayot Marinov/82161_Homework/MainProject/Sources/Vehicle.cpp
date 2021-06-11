#include "../Headers/Vehicle.h"
#include "../Headers/Person.h"
#include <cstddef>
#include<stdexcept>


const Registration& Vehicle::getRegistration() const {
    return this->registration;
}

const string Vehicle::getDesctiption() const {
    return this->description;
}

const Person& Vehicle::getOwner() const{
    if(!hasOwner()) {
        throw std::logic_error("    Vehicle does not have owner."); 
    }
    return *owner;
}

Vehicle::Vehicle(const Registration& reg, 
const string& desc) 
:registration(reg), description(desc), owner(nullptr) {
}

Vehicle::Vehicle(const string& reg, 
const string& desc) 
:registration(reg), description(desc), owner(nullptr) {
}

Vehicle::Vehicle(const char* reg, 
const char* desc) 
:registration(reg), description(desc), owner(nullptr) {
    owner = nullptr;
}
    
bool Vehicle::operator==(const Vehicle& rhs) {
    bool equal = (this->registration == rhs.getRegistration() &&
        this->description == rhs.getDesctiption());
    
    if(this->hasOwner() != rhs.hasOwner()) {
        equal = false;
    }
    else if (this->hasOwner() && rhs.hasOwner()) {
        equal = equal &&
            (*(this->owner) == rhs.getOwner());
    }
    return equal;         
}

void Vehicle::setOwner(Person* owner) {
    if(owner == nullptr)
        throw std::invalid_argument("Owner cannot be a nullptr.");
    this->owner = owner;
}

void Vehicle:: removeOwner(Person* owner) {
    if(!(this->owner == owner))
        throw std::invalid_argument("This is not the correct owner of the vehicle.");
    this->owner = nullptr;
}

bool Vehicle::hasOwner() const {
    return owner != nullptr;
}

void Vehicle::printDetailedInformation(std::ostream& out) const {
    out<<*this<<'\n';
    if(!hasOwner()) {
        out<<"This vehicle has no owner.\n";
    }
    else {
        out<<"Owner:\n";
        out<<"    "<<*(owner)<<'\n';
    }
    
}

std::ostream& operator<<(std::ostream& out, const Vehicle& v) {
    out<<"VEHICLE "<<v.getRegistration()<<' '<<v.getDesctiption();
    /*if(v.hasOwner())
        out<<' '<<v.getOwner();*/

    return out;
}
