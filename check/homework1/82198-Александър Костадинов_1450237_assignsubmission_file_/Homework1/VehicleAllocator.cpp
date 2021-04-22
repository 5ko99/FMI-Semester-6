#include "VehicleAllocator.h"

VehicleAllocator::VehicleAllocator()
{
    this->size = 0;

    this->vehicles = nullptr;
}
VehicleAllocator::~VehicleAllocator()
{
    for (size_t i = 0; i < this->size; i++)
    {
        delete this->vehicles[i];
    }

    delete[] this->vehicles;
}
Vehicle *VehicleAllocator::createVehicle()
{
    std::cout << "Enter vehicle registration: ";
    MyString registration = read_string();

    std::cout << "\nEnter vehicle description: ";
    MyString description = read_string();

    std::cout << "\nEnter how many spaces dose the vehicle take: ";
    size_t space;
    std::cin >> space;
    Vehicle *vehicleptr = new Vehicle(registration.c_str(), description.c_str(), space);

    return vehicleptr;
}

void VehicleAllocator::set_size(size_t size)
{
    try
    {
        if (this->size != 0)
        {
            throw std::logic_error("");
        }

        this->size = size;
        this->vehicles = new Vehicle *[size];
    }
    catch (std::logic_error)
    {
        std::cout << "\n****You cannot change already changed size!****\n";
    }
}

size_t VehicleAllocator::get_size() const
{
    return this->size;
}

void VehicleAllocator::allocate()
{
    for (size_t i = 0; i < this->size; i++)
    {
        this->vehicles[i] = createVehicle();
    }
}

Vehicle &VehicleAllocator::operator[](size_t index)
{
#ifdef DEBUG
    assert(index < this->size)
#endif

        return *(this->vehicles[index]);
}
