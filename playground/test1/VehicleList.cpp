#include "VehicleList.h"
#include "stdexcept"
#include "cassert"

VehicleList::VehicleList(std::size_t capacity) : allocated(capacity) {
    vehicles = new Vehicle *[capacity];
}

VehicleList::VehicleList(const VehicleList &other) {
    vehicles = clone(other.vehicles, other.allocated, other.used);
    allocated = other.allocated;
    used = other.used;
}

VehicleList::~VehicleList() {
    for (size_t i = 0; i < used; ++i)
        delete vehicles[i];

    delete[] vehicles;
}

VehicleList &VehicleList::operator=(const VehicleList &other) {
    if (this != &other) {
        Vehicle **copy = clone(other.vehicles, other.allocated, other.used);
        delete[] vehicles;
        vehicles = copy;
        allocated = other.allocated;
        used = other.used;
    }

    return *this;
}

void VehicleList::insert(const char *regnum, const char *description) {
    if (used >= allocated)
        throw std::exception();

    if (find(regnum))
        throw std::exception();

    vehicles[used] = new Vehicle(regnum, description);
    ++used;
}

const Vehicle &VehicleList::at(size_t index) const {
    if (index >= used)
        throw std::out_of_range("no such vehicle");
    return *vehicles[index];
}

const Vehicle &VehicleList::operator[](size_t index) const {
    assert(index < used);
    return *vehicles[index];
}

bool VehicleList::empty() const {
    return used == 0;
}

std::size_t VehicleList::capacity() const {
    return allocated;
}

std::size_t VehicleList::size() const {
    return used;
}

const Vehicle *VehicleList::find(const char *regnum) const {
    for (size_t i = 0; i < used; ++i)
        if (vehicles[i]->regnum == regnum)
            return vehicles[i];

    return nullptr;
}

Vehicle **VehicleList::clone(Vehicle **vehicles, size_t size, size_t used) {
    assert(used < size);

    Vehicle **copy = new Vehicle *[size];

    for (size_t i = 0; i < used; ++i)
        copy[i] = new Vehicle(*vehicles[i]);

    return copy;
}