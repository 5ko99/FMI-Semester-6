//
// Created by User on 5/7/2021.
//

#include "Person.h"
#include "Vehicle.h"
void swap(Person& first,Person& second){
    using std::swap;

    swap(first.name,second.name);
    swap(first.egn,second.egn);
    first.vehicles.swap(second.vehicles);
}
Person::Person() {
this->name= nullptr;
this->egn=0;
}

Person::Person(const std::string &name, const unsigned int egn) {
    this->name=name;
    this->egn=egn;
//    allPersons.push_back(new Person(*this));
}

Person::Person(const Person &other) {
this->name=other.name;
this->egn=other.egn;
    for (int i = 0; i < other.vehicles.size(); ++i) {
        this->vehicles.push_back(other.vehicles[i]);
    }
}

Person &Person::operator=(const Person &other) {

    Person temp(other);
    swap(*this,temp);

    return *this;
}

Person::~Person() {
this->name= nullptr;
this->egn=0;
this->vehicles.clear();
}

void Person::add_vehicle(Vehicle* v){
this->vehicles.push_back(v);
}

const std::string& Person::get_name()const {
    return this->name;
}

void Person::print_vehicles() const {
for(int i=0;i<vehicles.size();i++)
{
    std::cout<<vehicles[i]->get_reg().get_registration()<<" "<<vehicles[i]->get_description()<<std::endl;
}
}

const unsigned int& Person::get_egn()const{
    return this->egn;
}

const int &Person::vehicles_size() const {
    return this->vehicles.size();
}

Vehicle* Person::vehicle_pos(const int& pos) {
    return vehicles[pos];
}

void Person::remove_vehicle(const std::string& reg) {
    for(int i=0;i<vehicles.size();i++) {
        if (vehicles[i]->get_reg().get_registration()==reg){
            vehicles[i]->set_owner(nullptr);
            vehicles.erase(vehicles.begin()+i);
        }
    }
}

void Person::remove_vehicle() {
    vehicles[vehicles.size()-1]->set_owner(nullptr);
    vehicles.erase(vehicles.begin()+vehicles.size()-1);
}
