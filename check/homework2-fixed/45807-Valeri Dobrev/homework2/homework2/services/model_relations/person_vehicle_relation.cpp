#include "person_vehicle_relation.hpp"

void PersonVehicleRelation::acquire(const unsigned peronsId, const char* vehicleId){
    
    Person *person = PersonFactory::getInstance()->getById(peronsId);
    Vehicle *vehicle = VehicleFactory::getInstance()->getById(vehicleId);

    person->addVehicle(vehicle);
}

void PersonVehicleRelation::release(const unsigned peronsId, const char* vehicleId){
    
    Person *person = PersonFactory::getInstance()->getById(peronsId);
    Vehicle *vehicle = VehicleFactory::getInstance()->getById(vehicleId);

    person->removeVehicle(vehicle);
}
