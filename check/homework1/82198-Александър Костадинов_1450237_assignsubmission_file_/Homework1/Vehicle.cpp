#include "Vehicle.h"

Vehicle::Vehicle(const char *registration, const char *description, std::size_t space)
{
    if (!registration)
    {
        throw std::invalid_argument("****Registration required!****");
    }

    if (!description)
    {
        throw std::invalid_argument("****Description required!****");
    }

    if (!space)
    {
        throw std::invalid_argument("****Space must be at least 1!****");
    }

    this->registryNumber = registration;
    this->description = description;
    this->space = space;
}

const char *Vehicle::get_registration() const
{
    return this->registryNumber.c_str();
}

const char *Vehicle::get_description() const
{
    return this->description.c_str();
}

std::size_t Vehicle::get_space() const
{
    return this->space;
}

void swap(size_t i, size_t j, Vehicle **vehicle)
{
    if (i != j)
    {
        Vehicle *temp = vehicle[i];
        vehicle[i] = vehicle[j];
        vehicle[j] = temp;
    }
}
