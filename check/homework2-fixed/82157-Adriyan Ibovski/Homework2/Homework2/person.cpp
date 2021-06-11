#include "Person.h"
#include <iostream>

Person::Person(const string &name, unsigned int ID) : m_name(name), m_ID(ID) {
}

Person::~Person() {
    m_vehicles.clear();
}

void Person::addVehicle(Vehicle*& v) {
    for(Vehicle* m_v : m_vehicles){
        if(m_v == v) throw std::invalid_argument("This person has already owned that vehicle");
    }
    this->m_vehicles.push_back(v);

    v->setOwner(this);
}

const unsigned int Person::getID() const {
    return m_ID;
}

void Person::removeVehicle(const Registration &reg) {
    for(int it = 0; it < m_vehicles.size(); it++){
        if(m_vehicles[it]->getReg() == reg){
            m_vehicles[it]->setOwner(nullptr);
            m_vehicles[it] = m_vehicles.back();
            m_vehicles.pop_back();
        }
    }
}

bool Person::hasVehicles() {
    return !m_vehicles.empty();
}

void Person::releaseAllVehicles() {
    for(Vehicle *v : m_vehicles){
        v->setOwner(nullptr);
    }
}

std::string Person::getName() const {
    return m_name;
}

void Person::showAllVehicles() {
    for(Vehicle *v : m_vehicles){
        std::cout<<v->getReg().getString()<<" "<<v->getDesc()<<std::endl;
    }
}

