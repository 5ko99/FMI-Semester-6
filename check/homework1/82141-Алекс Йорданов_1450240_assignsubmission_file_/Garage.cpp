#include "Garage.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <cstring>


Garage::Garage(std::size_t size)
{
    vehicles = new Vehicle*[size];
    vehiclescount=0;
    capacity=size;

}
void Garage::insert(Vehicle& v)
{

    if(find(v.registration())) throw std::out_of_range("Duplicates!");
    if(v.space()>capacity) throw std::range_error("No more space!");
    Vehicle* vehicle=new Vehicle(v);
    vehicles[vehiclescount++]=vehicle;
    capacity-=v.space();
}
void Garage::erase(const char* registration)
{
    for(int i=0; i<vehiclescount; i++)
    {
        if(strcmp(registration,vehicles[i]->registration())==0)
        {
            capacity+=vehicles[i]->space();
            delete vehicles[i];
            vehicles[i]=vehicles[--vehiclescount];
            break;
        }
    }
}
const Vehicle& Garage::at(std::size_t pos) const
{
    if(pos>=vehiclescount) throw std::out_of_range("Out of range!");
    return *vehicles[pos];
}
const Vehicle& Garage::operator[](std::size_t pos) const
{
    return at(pos);
}
bool Garage::empty() const
{
    return vehiclescount==0;
}
std::size_t Garage::size() const
{
    return vehiclescount;
}
void Garage::clear()
{
    for(int i=0; i<vehiclescount; i++)
    {
        capacity+=vehicles[i]->space();
        delete vehicles[i];
    }
    vehiclescount=0;
}
const Vehicle* Garage::find(const char* registration) const
{
    for(int i=0; i<vehiclescount; i++)
    {
        if(strcmp(registration,vehicles[i]->registration())==0)
        {
            return vehicles[i];
        }
    }
    return nullptr;
}
Garage::~Garage()
{
    clear();
    delete[] vehicles;
}
