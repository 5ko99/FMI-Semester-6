#include "Person.h"


Person::Person(std::string name, unsigned int id) {
    this->name = name;
    this->id = id;
}

void Person::AddVehicle(const Vehicle &rhs) {
    this->VehicleList.push_back(rhs);
}

void Person::RemoveVehicle(std::string reg) {
    int i = 0;
    for (i; i < this->VehicleList.capacity(); i++) {
        if (strcmp(this->VehicleList.at(i).GetReg().registr(), reg.c_str()) == 0) {
            break;
        }
        this->VehicleList.erase(this->VehicleList.begin() + i);
    }
}

unsigned int Person::findByReg(char *reg) {
    try {
        for (int i = 0; i < this->VehicleList.capacity(); i++) {
            if (this->VehicleList.at(i).GetReg().registr() == reg) {
                return i;
            }
        }
        throw "NoSuchVehicle";
    }
    catch (...) {
        std::cout << "No such Vehicle found.\n";
    }
    return 0;
}

unsigned int Person::GetId() {
    return this->id;
}

void Person::RELEASE(std::string reg)
{
    for(int i= 0; i < this->VehicleList.size(); i++)
    {
        if(strcmp(this->VehicleList.at(i).GetReg().registr(), reg.c_str()) == 0) {
            this->VehicleList.erase(this->VehicleList.begin() + i);
            break;
        }
    }
}

bool Person::isEmpty()
{
    return this->VehicleList.empty();
}

void Person::RemoveVehicles()
{
    for(int i = 0; i < this->VehicleList.size(); i++) {
        this->VehicleList.at(i).RemovePerson();
    }
}

std::string Person::GetName() {
    return this->name;
}

Vehicle &Person::GetVehicle(int i) {
    return this->VehicleList.at(i);
}

unsigned int Person::GetSize() {
    return this->VehicleList.size();
}

