#include <iostream>
#include "Vehicle.h"
#include "VehicleList.h"
#include "Registration.h"

int main()
{
    unsigned int n;
    std::cout << "Number of vehicles: ";
    std::cin >> n;
    VehicleList vehiclelist = VehicleList(n);

    char* regnum = new char[9];
    char* description = new char[32];
    for (int i = 0; i < n; i++) {

        std::cout << "###################N" << i;
        std::cout << "Registration:";
        std::cin >> regnum;
        std::cout << "Description:";
        std::cin >> description;

        vehiclelist.insert(regnum, description);
    }

    char* input = new char[9];
    while (regnum) {
        std::cout << "Check if vehicle exists: ";
        std::cin >> input;

        if (vehiclelist.exist(input)) {
            std::cout << "This vehicle exists!" << std::endl;
        }
        else {
            std::cout << "This vehicle does not exist!" << std::endl;
        }
    }
}


#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP

#include <iostream>

class Registration
{
public:
    Registration(const char* str);
    Registration& operator=(const char* str);
    bool isValid(const char* str);
    bool operator==(const char* str) const;
    const char* toString() const;
    void setRegistration(const char* str);
    char* getRegNum();
private:
    char regNum[9];
};

#endif // !REGISTRATION_HPP_INCLUDED



#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <iostream>
#include "Registration.h";

class Vehicle
{
public:
    Registration regnum;
    std::string description;
    Vehicle(const char* regnum, const char* description);
    void setDescription(const char* str);
};

#endif // !VEHICLE_HPP_INCLUDED


#ifndef VEHICLELIST_HPP
#define VEHICLELIST_HPP

#include <iostream>
#include <vector>
#include "Vehicle.h";

class VehicleList
{
public:
    VehicleList(std::size_t capacity);
    ~VehicleList();
    void insert(const char* regnum, const char* description);
    const Vehicle& at(std::size_t index) const;
    const Vehicle& operator[](std::size_t index) const;
    bool empty() const;
    std::size_t capacity() const;
    std::size_t size() const;
    const Vehicle* find(const char* regnum) const;
    bool exist(const char* regnum) const;

private:
    std::size_t listcapacity;
    Vehicle** vehicles;
    unsigned int counter;
};

#endif // !VEHICLELIST_HPP_INCLUDED


Registration::Registration(const char* str) {
    this->setRegistration(str);
}

char* Registration::getRegNum() {
    return this->regNum;
}

bool Registration::operator==(const char* str) const {
    for (int i = 0; i < 9; i++) {
        if (this->regNum[i] != str[i]) {
            return false;
        }
    }

    return true;
}

Registration& Registration::operator=(const char* str) {
    if (!isValid(str)) {
        std::exception;
    }
    this->setRegistration(str);

    return *this;
}

bool Registration::isValid(const char* str) {
    for (int i = 0; i <= 1; i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }

    for (int i = 2; i < 9; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    return true;
}

void Registration::setRegistration(const char* str) {
    for (int i = 0; i < 9; i++) {
        this->regNum[i] = str[i];
    }
}



VehicleList::VehicleList(std::size_t capacity) {
    this->listcapacity = capacity;
    this->vehicles = new Vehicle * [capacity];
}


VehicleList::~VehicleList() {
    delete[] this->vehicles;
}

const Vehicle* VehicleList::find(const char* regnum) const {
    Vehicle* currentVehicle;

    for (int i = 0; i < this->counter; i++) {
        currentVehicle = this->vehicles[i];
        Registration currentRegnum = currentVehicle->regnum;

        if (std::strcmp(currentRegnum.getRegNum(), regnum)) {
            return currentVehicle;
        }
    }

    return nullptr;
}
std::size_t VehicleList::size() const {
    return this->counter;
}
std::size_t VehicleList::capacity() const {
    return this->listcapacity;
}
bool VehicleList::empty() const {
    if (this->counter == 0) {
        return true;
    }

    return false;
}

const Vehicle& VehicleList::operator[](std::size_t index) const {
    return *this->vehicles[index];
}

const Vehicle& VehicleList::at(std::size_t index) const {
    try {
        return *this->vehicles[index];
    }
    catch (...) {
        std::out_of_range;
    }
}

void VehicleList::insert(const char* regnum, const char* description) {
    Vehicle vehicle = Vehicle(regnum, description);

    if (this->counter == this->listcapacity || this->exist(regnum)) {
        std::exception;
    }

    this->vehicles[this->counter] = &vehicle;
    counter++;
}

bool VehicleList::exist(const char* regnum) const {
    Vehicle* currentVehicle;

    for (int i = 0; i < this->counter; i++) {
        currentVehicle = this->vehicles[i];
        Registration currentRegnum = currentVehicle->regnum;

        if (std::strcmp(currentRegnum.getRegNum(), regnum)) {
            return true;
        }
    }

    return false;
}

