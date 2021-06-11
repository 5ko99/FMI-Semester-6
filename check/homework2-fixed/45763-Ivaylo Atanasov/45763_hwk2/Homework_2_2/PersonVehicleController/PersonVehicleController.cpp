#include "PersonVehicleController.hpp"


PersonVehicleController::~PersonVehicleController(){
    clear();
}

void PersonVehicleController::clear(){
    for(std::size_t i=0; i<vehiPointerArr.size(); i++){
        delete vehiPointerArr.at(i);
    }
    for(std::size_t i=0; i<personPointerArr.size(); i++){
        delete personPointerArr.at(i);
    }
    vehiPointerArr.clear();
    personPointerArr.clear();
}


void PersonVehicleController::createPerson(std::string nameStr, std::string uidStr){
    if(!strcmp(uidStr.c_str(), "\0")) throw std::invalid_argument("uid not found");
    const unsigned int uid = strToInt(uidStr);
    if(personExists(uid)){
        throw std::invalid_argument("person with this uid already exists");
    } else {
        Person* pers = new Person(nameStr, uid);
        personPointerArr.push_back(pers);
    }
}


void PersonVehicleController::createVehicle(std::string regStr, std::string descStr){
    if(!strcmp(descStr.c_str(), "\0")) throw std::invalid_argument("description not found");
    Registration reg(regStr.c_str());
    if(vehicleExists(reg)){
        throw std::invalid_argument("vehicle with this registration already exists");
    } else {
        Vehicle* veh = new Vehicle(reg, descStr);
        vehiPointerArr.push_back(veh);
    }
    
}


void PersonVehicleController::acquire(std::string personIdStr, std::string vehiRegStr){
    Person* persp = getPersonById(strToInt(personIdStr));
    Registration reg(vehiRegStr.c_str());
    Vehicle* vehip = getVehicleById(reg);
    persp->acquire(*vehip);
}


void PersonVehicleController::release(std::string personIdStr, std::string vehiRegStr){
    Person* persp = getPersonById(strToInt(personIdStr));
    Registration reg(vehiRegStr.c_str());
    persp->release(reg);
}


void PersonVehicleController::remove(std::string whatStr){
    std::size_t whatId = getIdentificatorType(whatStr);
    if(whatId == 1){
        Registration reg(whatStr.c_str());
        Vehicle* vehip = getVehicleById(reg);
        if(vehip->getOwnerPtr() != nullptr) {
            vehip->getOwner().release(reg);
        }
        for(int i=0; i<vehiPointerArr.size(); i++){
            if(vehiPointerArr.at(i)->getReg() == reg){
                delete vehiPointerArr.at(i);
                vehiPointerArr.erase(vehiPointerArr.begin() + i);
            }
        }
    } else if(whatId == 2){
        unsigned int uid = strToInt(whatStr.c_str());
        Person* persp = getPersonById(uid);
        persp->releaseAll();
        for(int i=0; i<personPointerArr.size(); i++){
            if(personPointerArr.at(i)->getUid() == uid){
                delete personPointerArr.at(i);
                personPointerArr.erase(personPointerArr.begin() + i);
            }
        }
    } else {
        throw std::invalid_argument("no such person or vehicle was found");
    }
}

void PersonVehicleController::show(std::string whatStr){
    if(strcmp(toUpperCase(whatStr).c_str(), "PEOPLE") == 0){
        printPersons();
    }
    else if(strcmp(toUpperCase(whatStr).c_str(), "VEHICLES") == 0){
        printVehicles();
    } else {
        std::size_t whatId = getIdentificatorType(whatStr);
        if(whatId == 1){
            Registration reg(whatStr.c_str());
            Vehicle* vehip = getVehicleById(reg);
            vehip->printWithOwner();
            std::cout<<"\n";
        } else if (whatId == 2){
            unsigned int uid = strToInt(whatStr);
            Person* persp = getPersonById(uid);
            persp->printWithVehicles();
            std::cout<<"\n";
        } else {
            throw std::invalid_argument("no such person or vehicle was found");
        }
    }
}



bool PersonVehicleController::personExists(const unsigned int& uid){
    for(std::size_t i=0; i<personPointerArr.size(); i++){
        if(personPointerArr.at(i)->getUid() == uid) return true;
    }
    return false;
}
bool PersonVehicleController::vehicleExists(Registration& reg){
    for(std::size_t i=0; i<vehiPointerArr.size(); i++){
        if(vehiPointerArr.at(i)->getReg() == reg) return true;
    }
    return false;
}



Vehicle* PersonVehicleController::getVehicleById(const Registration& reg){
    for(std::size_t i=0; i<vehiPointerArr.size(); i++){
        if(vehiPointerArr.at(i)->getReg() == reg) return vehiPointerArr.at(i);
    }
    throw std::invalid_argument("no vehicle found");
}
Person* PersonVehicleController::getPersonById(const unsigned int id){
    for(std::size_t i=0; i<personPointerArr.size(); i++){
        if(personPointerArr.at(i)->getUid() == id)return personPointerArr.at(i);
    }
    throw std::invalid_argument("no person found");
}



std::size_t PersonVehicleController::getIdentificatorType(std::string whatStr){
    // 0 = neither
    // 1 = vehicle registration
    // 2 = person uid
    try{
        Registration reg(whatStr.c_str());
        return 1;
    } catch (const std::exception& e){
        try{
            strToInt(whatStr);
            return 2;
        } catch (const std::exception& e){
            return 0;
        }
    }
}



void PersonVehicleController::printPersons() const{
    for(std::size_t i=0;i<personPointerArr.size();i++){
        personPointerArr.at(i)->print();
        std::cout<<"\n";
    }
}
void PersonVehicleController::printVehicles() const{
    for(std::size_t i=0;i<vehiPointerArr.size();i++){
        vehiPointerArr.at(i)->print();
        std::cout<<"\n";
    }
}
void PersonVehicleController::printAll() const{
    for(std::size_t i=0;i<personPointerArr.size();i++){
        personPointerArr.at(i)->printWithVehicles();
        std::cout<<"\n";
    }
    printVehicles();
}
