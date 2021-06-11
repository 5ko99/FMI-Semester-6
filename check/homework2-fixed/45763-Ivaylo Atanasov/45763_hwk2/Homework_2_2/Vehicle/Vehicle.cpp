#include "Vehicle.hpp"



void Vehicle::copy(const Vehicle& veh){
    this->registration = veh.registration;
    this->description = veh.description;
    this->owner = veh.owner;
}



Vehicle::Vehicle(const Registration& reg, const std::string& desc):registration(reg),description(desc){
    owner = nullptr;
}

bool Vehicle::operator==(const Vehicle& veh) const{
    return !strcmp(this->getReg().toCharArr(), veh.getReg().toCharArr());
}



Person& Vehicle::getOwner() const{
    return *owner;
}
Person* Vehicle::getOwnerPtr() const{
    return owner;
}
const Registration& Vehicle::getReg() const{
    return registration;
}
const std::string& Vehicle::getDesc() const{
    return description;
}



void Vehicle::print() const{
    std::cout<<"<"<<registration.toCharArr()<<", "<<description<<">";
}
void Vehicle::printWithOwner() const{
    std::cout<<"<"<<registration.toCharArr()<<", "<<description<<"> owner: ";
    if(owner != nullptr)owner->print();
    else std::cout<<"none";
}




