#include "vehicle.hpp"
#include "../person/person.hpp"

Vehicle::Vehicle(const char* registration, const std::string& description) : registration(registration), description(description), owner(nullptr){
}

Vehicle::~Vehicle(){
    owner = nullptr;
}

Vehicle::Vehicle(const Vehicle& other): Vehicle(other.registration.toString(), other.description){
    this->owner = other.owner;
}

Vehicle& Vehicle::operator=(const Vehicle& vehicle){
    if(this == &vehicle) return *this;

    this->registration = vehicle.registration;
    this->description = vehicle.description;
    this->owner = vehicle.owner;

    return *this;
}

const bool Vehicle::operator==(const char* registration) const{
    if(!registration) throw std::invalid_argument("Registration should not be null!");
    return this->registration == registration;
}
const Registration& Vehicle::getId() const{ return registration;}

const std::string& Vehicle::getDescription() const{ return this->description; }

const Person* Vehicle::getOwner() const{ return this->owner; }


const bool Vehicle::needConfirmToDelete()const{
    return owner!=nullptr;
}

void Vehicle::prepareForDelete(){
    setOwner(nullptr);
}

const std::string Vehicle::getClassName(){ return "Vehicle";}

const std::string Vehicle::getIdToString()const { return std::string(registration.toString());}


void Vehicle::setOwner(Person* owner){    
    //Checks if we try to reacquire a vehicle
    if(owner == this->owner && owner) throw std::invalid_argument("Vehicle already acquired by this person!");


    if(this->owner){
        this->owner->remove(this);
    }
    
    if(owner){
        owner -> add(this);
    }
    this->owner = owner;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& v){
    os<<"Registration: "<<v.getIdToString()<< " Description: "<<v.getDescription();
    return os;
}

