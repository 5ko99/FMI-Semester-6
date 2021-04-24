#include "Garage.h"

Garage::Garage(std::size_t otherCapacity) {
    capacity = otherCapacity;
    counter = 0; //by default the counter is 0 since this is the initial creation
    lastIndex = 0; //by default the last index is 0 since this is the initial creation

    Vehicle** vehicles = new Vehicle*[capacity];
}

Garage::Garage(const Garage& other) {
    capacity = other.capacity;
    counter = other.counter;
    lastIndex = other.lastIndex;

    Vehicle** newVehicles = new(std::nothrow) Vehicle*[capacity];

    for(std::size_t  i=0; i < counter; i++) {
        newVehicles[i] = other.vehicles[i];
    }

    vehicles = newVehicles;
}

Garage::~Garage() {
    delete[] vehicles;
    counter = 0; 
    lastIndex = 0;
}

void Garage::insert(Vehicle& v) {
    bool exists = 0; //a flag for an already existing vehicle - we cannot insert it!

    for(std::size_t i = 0; i < lastIndex; i++) {
        if(strcmp(vehicles[i]->registration(), v.registration()) == 0 ) {
            exists = 1;
            throw std::invalid_argument("The vehicle already exists!"); //throws an exception and doesn't insert the vehicle
            return;
        }
    }

    if(counter + v.space() > capacity) { //the space would be more than the capacity
        throw std::out_of_range("Not enough capacity in the garage!"); //throws an exception and doesn't insert the vehicle
        return;
    } else {
        vehicles[lastIndex] = &v;
        counter++; //we have 1 more vehicle - increasing the counter
        lastIndex++; //increasing the last index

        std::cout<<"Successfully inserted!"<<std::endl; //this is not necessarily needed, but is useful for the user
    }
}

void Garage::erase(const char* registration) {
    if (lastIndex == 0) {
        throw std::invalid_argument("Empty garage!"); //if the garage is empty, we can't erase anything
        return;
    }

    std::size_t eraseIndex = 0; //the index where we would be erasing

    for(std::size_t i = 0; i < lastIndex; i++) {
        if (strcmp(vehicles[i]->registration(),registration) == 0) {
            std::cout<<"Found the vehicle to remove!"<<std::endl; 

            eraseIndex = i; //we have found the vehicle to erase
        } else {
            std::cout<<"Couldn't find the vehicle to remove!";
            return;
        }
    }
    
    if (eraseIndex >= 0) {
        for (std::size_t i = eraseIndex; i < lastIndex; i++) {
            vehicles[i] = vehicles[i+1]; 
        }

        lastIndex--; //the last index is less by 1 since we have -1 vehicles
        counter--; //the counter is also less by 1
    }
}

const Vehicle& Garage::at(std::size_t pos) const {
    return *vehicles[pos];
}

const Vehicle& Garage::operator[](std::size_t pos) const {
    return *vehicles[pos];
}

bool Garage::empty() const {
    return counter == 0;
}

std::size_t Garage::size() const {
    return counter;
}

void Garage::clear() {
    lastIndex = 0;
    counter = 0;
}

const Vehicle* Garage::find(const char* registration) const {
    for(std::size_t i = 0; i < lastIndex; i++) {
        if(strcmp(vehicles[i]->registration(), registration) == 0) {
            std::cout<<"Successfully found!"<<std::endl; //a message for the user
            
            return vehicles[i];
        } 
    }

    std::cout<<"Not found in the garage!"<<std::endl;
    return nullptr;
}