#include <iostream>
#include <cstring>
#include "vehicle.h"
#include "garage.h"

// Ще съм много благодарна, ако получа обратна връзка с коментар за решението
// Благодаря предварително :)
// Използвам VS Code, компилатор MinGW


/*void Garage::print()
{
    std::cout << "taken spots: " << takenSpots << " ";
    for (std::size_t i = 0; i < takenSpots; ++i)
    {
        if (vehicles[i] != nullptr)
            std::cout << vehicles[i]->registration() << " ";
    }
}*/

Garage::Garage(std::size_t size)
{
    this->capacity = size;
    vehicles = new Vehicle * [size];
    for (std::size_t i = 0; i < size; ++i)
        vehicles[i] = nullptr;
}

Garage::~Garage()
{
    delete[] vehicles;
}

Garage::Garage(const Garage& other) // copy
{
    this->numberOfVehicles = other.numberOfVehicles;
    this->takenSpots = other.takenSpots;
    this->capacity = other.capacity;

    this->vehicles = new Vehicle * [capacity];
    for (std::size_t i = 0; i < capacity; ++i)
        this->vehicles[i] = other.vehicles[i];
}

Garage& Garage::operator = (const Garage& other) // copy assignment
{
    if (this != &other)
    {
        delete[] vehicles;
        this->takenSpots = other.takenSpots;
        this->capacity = other.capacity;
        this->numberOfVehicles = other.numberOfVehicles;

        this->vehicles = new Vehicle * [capacity];
        for (std::size_t i = 0; i < capacity; ++i)
            this->vehicles[i] = other.vehicles[i];
    }
    return *this;
}

void Garage::insert(Vehicle& v)
{
    if (v.space() + takenSpots > capacity)
        return;


    for (std::size_t i = 0; i < takenSpots; i += vehicles[i]->space())
    {
        if (strcmp(vehicles[i]->registration(), v.registration()) == 0)
            return;

    }

    //vehicles[takenSpots] = &v;
    for (std::size_t i = 0; i < v.space(); ++i)
    {
        vehicles[takenSpots + i] = &v;
    }
    takenSpots += v.space();
    numberOfVehicles++;
}

void Garage::erase(const char* registration)
{
    int index = -1;
    unsigned int freedSpace;
    for (std::size_t i = 0; i < this->takenSpots; i += vehicles[i]->space())
    {
        if (&vehicles[i] != nullptr && strcmp(registration, vehicles[i]->registration()) == 0)
        {
            takenSpots -= vehicles[i]->space();
            freedSpace = vehicles[i]->space();
            index = (int)i;
            

            for (std::size_t j = 0; j < freedSpace; ++j)
            {
                //delete[] vehicles[i + freedSpace];  // not sure
                vehicles[i + freedSpace] = nullptr;
            }
            break;
        }
    }

    if (index == -1)
        return;

    for (std::size_t i = index; i < this->takenSpots - 1; ++i)
    {
        vehicles[i] = vehicles[i + 1];
    }

    numberOfVehicles--;

}

const Vehicle& Garage::at(std::size_t pos) const
{
    std::size_t index = 0;
    for (std::size_t i = 0; i < capacity; i += vehicles[i]->space())
    {
        if (index == pos)
        {
            index = i;
            break;
        }
        index++;
    }
    return *vehicles[index];
}

const Vehicle& Garage::operator[](std::size_t pos) const
{
    return at(pos);
}

bool Garage::empty() const
{
    return takenSpots == 0;
}

std::size_t Garage::size() const
{
    return numberOfVehicles;
}

void Garage::clear()
{
   // delete[] vehicles;
    for (std::size_t i = 0; i < capacity; ++i)
        vehicles[i] = nullptr;
    takenSpots = 0;
    numberOfVehicles = 0;

}

const Vehicle* Garage::find(const char* registration) const
{
    for (std::size_t i = 0; i < capacity; ++i)
    {
        if (&vehicles[i] != nullptr && strcmp(vehicles[i]->registration(), registration) == 0)
            return vehicles[i];
    }
    return nullptr;
}
