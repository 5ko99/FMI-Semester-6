#include "garage.h"
#include <iostream>
#include <cassert>

//Rule of 3
Garage::Garage(size_t size)
{
    //the garage may contain maximum 'size' vehicles 
    //(in the case every vehicle costs 1 space)
    vehicles = new Vehicle* [size]; 

    vehiclesCount = 0;
    capacity = size;
    freeSpace = capacity;
}

Garage::Garage(Garage& other)
{
    this->vehicles = new Vehicle* [other.capacity];
    this->capacity = other.capacity;
    for (size_t i=0; i<other.vehiclesCount; i++){
        this->vehicles[i] = other.vehicles[i];
    }
    this->vehiclesCount = other.vehiclesCount;
    this->freeSpace = other.freeSpace; 
}

Garage& Garage::operator=(Garage& other)
{
    if (this == &other){
        return *this;
    }
    this->vehicles = new Vehicle* [other.capacity];
    this->capacity = other.capacity;
    for (size_t i=0; i<other.vehiclesCount; i++){
        this->vehicles[i] = other.vehicles[i];
    }
    this->vehiclesCount = other.vehiclesCount;
    this->freeSpace = other.freeSpace; 
    return *this;
}

Garage::~Garage()
{
    for (size_t i=0; i<vehiclesCount; i++){
        delete vehicles[i];
    }
    delete [] vehicles;
    vehicles = nullptr;
    capacity = 0;
    freeSpace = 0;
    vehiclesCount = 0;
}

//Other methods
void Garage::insert(Vehicle& v)
{
    if (find(v.registration())){
        throw "This vehicle is already in the garage!";
    }
    
    if (v.space() > freeSpace){
        throw "Not enough space in the garage! The vehicle is too big!";
    }
     
    vehicles[vehiclesCount] = &v;
    vehiclesCount++;
    freeSpace -= v.space(); 
    std::cout << "Vehicle successfully added!" << std::endl;
}

void Garage::erase(const char* registration)
{
    for (size_t i=0; i<vehiclesCount; i++){
        //"converting" registrations to MyString to use operator== instead of strcmp
        if (MyString(vehicles[i]->registration()) == MyString(registration)){
            freeSpace += vehicles[i]->space();
            vehicles[i] = vehicles[vehiclesCount-1];
            vehicles[vehiclesCount-1] = nullptr;
            vehiclesCount--;
            std::cout << "Vehicle successfully removed!" << std::endl;
            return;
        }
    }
    std::cout << "There is no such vehicle in the garage!" << std::endl;
}

const Vehicle& Garage::at(size_t pos) const
{
    if (pos >= vehiclesCount){
        throw std::out_of_range("Invalid position");
    }
    return *vehicles[pos];
}

const Vehicle& Garage::operator[](size_t pos) const 
{
    assert(pos < vehiclesCount);
    return at(pos);
}

bool Garage::empty() const {return !(vehiclesCount);}

size_t Garage::size() const {return vehiclesCount;}

void Garage::clear()
{
    while (vehiclesCount){
        erase(vehicles[vehiclesCount-1]->registration());
    }
    std::cout << "Garage cleared successfully!" << std::endl;
}

const Vehicle* Garage::find(const char* registration) const
{
    for (size_t i=0; i<vehiclesCount; i++){
        if (MyString(vehicles[i]->registration()) == MyString(registration)){
            return vehicles[i];
        }
    }
    return nullptr;
}

    