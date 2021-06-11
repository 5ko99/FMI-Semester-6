#include "../Headers/Person.h"
#include "../Headers/Vehicle.h"
#include "../Headers/ArrayOfPointersUtils.h"
#include <string>
#include <cstddef>
using std::string;

class Vehicle;

const size_t DEFAULT_ARRAY_SIZE = 4;

Person::Person(const string& n)
        :name(n), 
        id(nextId++) {
}

Person::Person(const char* n)
        :name(n), 
        id(nextId++) {
}

Person::Person(const string& n, vector<const Vehicle*> v)
        :name(n),
        vehicles(v),
        id(nextId++) {
}

Person::Person(const char* n, vector<const Vehicle*> v)
        :name(n),
        vehicles(v), 
        id(nextId++) {
}

Person::Person(const Person& rhs)
        :name(rhs.name), vehicles(rhs.vehicles), id(nextId++) {
}

Person& Person::operator=(const Person& rhs) {
    if(this!= &rhs) {
        this->name = rhs.name;
        this->vehicles = rhs.vehicles;
    }

    return *this;
}

bool Person::operator==(const Person& rhs) {
    return (id == rhs.id);
}

void Person::addVehicle(const Vehicle* v) {
    vehicles.push_back(v);
}

void Person::removeVehicle(const Vehicle* v) {
    for (size_t i = 0; i < vehicles.size(); i++) {
        if(vehicles[i] == v)
            vehicles.erase(vehicles.begin() + i);
    }
}

const char* Person::getName() const {
    return name.c_str();
}

size_t Person::getId() const {
    return id;
}

size_t Person::getNumberOfVehicles() const {
    return vehicles.size();
}

void Person::printDetailedInformation(std::ostream& out) const {
    out<<*this<<'\n';
    if(getNumberOfVehicles() == 0) {
        out<<"      No vehicles available.\n";
    }
    else {
        out<<"Vehicles:\n";
        for (size_t i = 0; i < getNumberOfVehicles(); i++) {
            out<<"    "<<*(vehicles[i])<<'\n';
        }
    }
    
}

std::ostream& operator<<(std::ostream& out, const Person& p) {
    out<<"PERSON \""<<p.getName()<<"\" "<<p.getId()/*<<' '<<p.getNumberOfVehicles()*/;

    return out;
}

size_t Person::nextId = 0;
