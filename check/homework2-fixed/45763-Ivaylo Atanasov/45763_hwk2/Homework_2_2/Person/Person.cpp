#include "Person.hpp"


Person::Person(const std::string& newName, const unsigned int& newUid):name(newName),uid(newUid){}


void Person::acquire(Vehicle& vehi){
    if(vehi.owner != nullptr){
        vehi.owner->release(vehi.getReg());
    }
    vehiArr.push_back(&vehi);
    vehi.owner = this;
}
void Person::release(const Registration& reg){
    bool wasFound = false;
    for(std::size_t i=0; i<vehiArr.size(); i++){
        if(vehiArr.at(i)->getReg() == reg){
            vehiArr.at(i)->owner = nullptr;
            vehiArr.erase(vehiArr.begin() + i);
            wasFound = true;
        }
    }
    if(!wasFound) throw std::invalid_argument("vehicle isnt owned by this person");
}
void Person::releaseAll(){
    for(std::size_t i=0; i<vehiArr.size(); i++)
        vehiArr.at(i)->owner = nullptr;
    vehiArr.clear();
}
bool Person::owns(const Registration &reg){
    for(std::size_t i=0; i<vehiArr.size(); i++){
        if(vehiArr.at(i)->getReg() == reg)return true;
    }
    return false;
}



const std::string& Person::getName() const{
    return name;
}
const unsigned int& Person::getUid() const{
    return uid;
}
const bool Person::hasVehicles() const{
    return vehiArr.size();
}



void Person::print() const{
    std::cout<<"("<<name<<", "<<uid<<")";
}
void Person::printWithVehicles() const{
    std::cout<<"("<<name<<", "<<uid<<"){";
    for(std::size_t i=0; i<vehiArr.size(); i++){
        std::cout<<"\n    ";
        vehiArr[i]->print();
    }
    vehiArr.size()==0?std::cout<<"}\n":std::cout<<"\n}";
}
