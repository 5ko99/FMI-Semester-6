//
// Created by User on 5/7/2021.


#include "Person.h"
#include "Vehicle.h"
void swap(Vehicle& first,Vehicle& second){
    using std::swap;

    swap(first.reg,second.reg);
    swap(first.description,second.description);
    swap(first.owner,second.owner);
}

Vehicle::Vehicle(const Registration& reg, const std::string &description):reg(reg),description(description),owner(nullptr)
{
    for (int i=0;i<allVehicles.size();i++){
        if(reg==allVehicles[i]->get_reg().get_registration())throw std::out_of_range("Registration already existing");
    }
}

Vehicle::Vehicle(const Vehicle &other):reg(other.reg),description(other.description){
//this->reg=other.reg;
//this->description=other.description;
if(other.owner!= nullptr)this->owner=new Person(*other.owner);
else this->owner= nullptr;
}

Vehicle &Vehicle::operator=(const Vehicle &other) {
    Vehicle temp(other);

    swap(*this,temp);

    return *this;
}

Vehicle::~Vehicle() {
this->description= nullptr;
this->owner= nullptr;
}

void Vehicle::set_owner(Person* person) {
this->owner=person;//new Person(person);
}

Person* Vehicle::get_owner() const {
    return this->owner;
}

const Registration& Vehicle::get_reg() const {
    return this->reg;
}

const std::string &Vehicle::get_description() const {
    return this->description;
}

