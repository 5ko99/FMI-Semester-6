
#include "Vehicle.h"



Vehicle::Vehicle(Registration reg,std::string descr, Person owner){
    this->descr=descr;
    this->reg=reg;
    this->owner=owner;
}

Vehicle::Vehicle(){

}

Registration& Vehicle::getRegVeh(){
    return this->reg;
}

std::string& Vehicle::getRegVehStr(){

    return this->getRegVeh().getReg();
}

std::string& Vehicle::getDescr(){
    return this->descr;
}

Person& Vehicle::getPerVeh(){

    return this->owner;
}
