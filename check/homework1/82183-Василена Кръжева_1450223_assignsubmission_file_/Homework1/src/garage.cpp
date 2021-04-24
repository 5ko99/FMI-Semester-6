#include <iostream>
#include <assert.h>
#include <cstring>
#include "../include/garage.hpp"

//helper function
int Garage::findIndex(const char* registration) const
{
    for (size_t i = 0; i < vehicles; i++)
    {
        if(strcmp((*garage[i]).registration(), registration)==0)
        {
            return i;
        }
    }

    return -1;
}

void Garage::copy(Vehicle** garage, size_t vehicles, size_t usedSpace, size_t capacity)
{
    if(this->capacity < capacity)
    {
        Vehicle** tmp = new Vehicle*[capacity];
        delete[] this->garage;

        this->garage = tmp;
    }

    for (size_t i = 0; i < vehicles; i++)
    {
        this->garage[i] = garage[i];
    }
    
    this->vehicles = vehicles;
    this->usedSpace = usedSpace;
    this->capacity = capacity;
}

Garage::Garage(std::size_t size) : vehicles(0), usedSpace(0), capacity(size)
{
    garage = new Vehicle* [size];
}

Garage::Garage(const Garage& other) 
                : garage(nullptr), vehicles(0), usedSpace(0), capacity(0)
{
    copy(other.garage, other.vehicles, other.usedSpace, other.capacity);
}

Garage& Garage::operator=(const Garage& other)
{
    copy(other.garage, other.vehicles, other.usedSpace, other.capacity);
    return *this;
}

Garage::~Garage()
{
    delete[] garage;
}

void Garage::insert(Vehicle& v)
{
    if(findIndex(v.registration()) > -1)
    {
        throw std::invalid_argument("The vehicle is already in the garage");
    }

    if(usedSpace + v.space() > capacity)
    {
        throw std::length_error("There's not enough space in the garage for the car");
    }

    if(v.space() == 0)
    {
        throw std::invalid_argument("Vehicle can't have zero parking space!");
    }

    garage[vehicles++] = &v;
    usedSpace += v.space();
}

void Garage::erase(const char* registration)
{
    int toBeErased = findIndex(registration);
    if(toBeErased > -1)
    {
        if(vehicles > 1){
            usedSpace -= garage[toBeErased]->space();
            garage[toBeErased] = garage[--vehicles];
        }
        else{
            //we are erasing the only vehicle in the garage
            vehicles = 0;
            usedSpace = 0;
        }
    }
}

const Vehicle& Garage::at(std::size_t pos) const
{
    if(pos < 0 || pos >= vehicles){
        throw std::out_of_range("Invalid position");
    }

    return *garage[pos];
}

const Vehicle& Garage::operator[](std::size_t pos) const
{
    assert(pos >=0 && pos < vehicles);

    return *garage[pos];
}

bool Garage::empty() const
{
    return (usedSpace == 0);    //could be !usedSpace but it's easier to read that way
}

std::size_t Garage::size() const
{
    return vehicles;
}

void Garage::clear()
{
    vehicles = 0;
    usedSpace = 0;
}

const Vehicle* Garage::find(const char* registration) const
{
    int index = findIndex(registration);

    if(index >= 0)
    {
        return garage[index];
    }

    return nullptr;   
}