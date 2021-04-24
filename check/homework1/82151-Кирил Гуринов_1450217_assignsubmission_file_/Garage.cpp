#include "Garage.h"

Garage::Garage(std::size_t size)
{
    this->memSize = size;
    this->free = size;
    this->occupied = 0;
    this->parkingSpaces = new Vehicle *[memSize];

}

void Garage::insert(Vehicle &v)
{
    if (free < v.space())
        throw "Not enough space";

    String numberToSearch = String(v.registration());
    for (std::size_t i = 0; i < this->occupied && this->occupied != 0; i++)
    {
        String number = String(parkingSpaces[i]->registration());
        if (number == numberToSearch)
            throw "Vehicle already in garage";
    }

    this->free = this->free - v.space();

    parkingSpaces[occupied] = &v;
    this->occupied++;
}

void Garage::erase(const char *registration)
{
    bool notFound = true;
    String numberToSearch = String(registration);
    for (std::size_t i = 0; i < this->occupied && notFound; i++)
    {
        String number = String(parkingSpaces[i]->registration());
        if (number == numberToSearch)
        {
            notFound = false;
            this->free = this->free + parkingSpaces[i]->space();
            for (std::size_t j = i; j < this->occupied; j++)
            {
                parkingSpaces[j] = parkingSpaces[j + 1];
            }
            this->occupied--;
        }
    }
}

const Vehicle &Garage::at(std::size_t pos) const
{
    if (pos < 0 || pos > memSize)
    {
        throw std::out_of_range("Given position of vehicle is out of range!");
    }
    return *this->parkingSpaces[pos];
}

const Vehicle &Garage::operator[](std::size_t pos) const
{
    //assert(pos < 0 || pos > memSize);
    return *this->parkingSpaces[pos];
}

bool Garage::empty() const
{
    if (this->occupied == 0)
        return true;
    return false;
}

std::size_t Garage::size() const
{
    return this->occupied;
}

void Garage::clear()
{
    delete[] parkingSpaces;
    occupied = 0;
    free = this->memSize;
}

const Vehicle *Garage::find(const char *registration) const
{
    bool notFound = true;
    String numberToSearch = String(registration);
    for (std::size_t i = 0; i < this->occupied && notFound; i++)
    {
        String number = String(parkingSpaces[i]->registration());
        if (number == numberToSearch)
        {
            return parkingSpaces[i];
        }
    }
    return nullptr;
}
