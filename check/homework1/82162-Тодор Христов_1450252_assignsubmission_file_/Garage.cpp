#include "Garage.h"

Garage::Garage(std::size_t size):capacity(size){}

Garage::Garage(const Garage& other): capacity(other.capacity),
	currentCapacity(other.currentCapacity), numberOfVehicles(other.numberOfVehicles){
	vehicles = new Vehicle * [numberOfVehicles];
	for (std::size_t i = 0; i < numberOfVehicles; i++) {
		vehicles[i] = other.vehicles[i];
	}
}

Garage& Garage::operator=(const Garage& other){
	if(this != &other){
		capacity = other.capacity;
		currentCapacity = other.currentCapacity;
		numberOfVehicles = other.numberOfVehicles;
		vehicles = new Vehicle * [numberOfVehicles];
		for (std::size_t i = 0; i < numberOfVehicles; i++) {
			vehicles[i] = other.vehicles[i];
		}
	}
	return *this;
}

Garage::~Garage(){
	delete[] vehicles;
}

void Garage::insert(Vehicle& v)
{
	if (find(v.registration()) != nullptr) {
		throw std::exception("it is existing registration");
	}
	if (capacity < currentCapacity + v.space()) {
		throw std::exception("there is not enough space");
	}
	Vehicle** copy = new Vehicle*[numberOfVehicles+1];
	for (std::size_t i = 0; i < numberOfVehicles; i++) {
		copy[i] = vehicles[i];
	}
	delete[] vehicles;
	copy[numberOfVehicles] = &v;
	numberOfVehicles++;
	currentCapacity += v.space();
	vehicles = copy;
}

void Garage::erase(const char* registration)
{
	if (!find(registration))
	{
		for (size_t i = 0; i < numberOfVehicles; i++)
		{
			if (strcmp(vehicles[i]->registration(),registration) == 0) {
				Vehicle* temp = vehicles[i];
				vehicles[i] = vehicles[numberOfVehicles - 1];
				vehicles[numberOfVehicles - 1] = nullptr;
				Vehicle** copy = new Vehicle*[numberOfVehicles - 1];
				for (std::size_t i = 0; i < numberOfVehicles - 1; i++) {
					copy[i] = vehicles[i];
				}
				delete[]vehicles;
				vehicles = copy;
				numberOfVehicles--;
				currentCapacity -= temp->space();
			}
		}
	}
	else {
		throw std::exception("there is no such registration");
	}
}

const Vehicle& Garage::at(std::size_t pos) const
{
    if (pos < 0 || pos > numberOfVehicles){
        throw std::exception("wrong pos");
    }
	return *vehicles[pos - 1];
}

const Vehicle& Garage::operator[](std::size_t pos) const
{
	return *vehicles[pos - 1];
}

bool Garage::empty() const
{
	return !numberOfVehicles;
}

std::size_t Garage::size() const
{
	return numberOfVehicles;
}

void Garage::clear()
{
	delete[] vehicles;
	currentCapacity = 0;
	numberOfVehicles = 0;
}

const Vehicle* Garage::find(const char* registration) const
{
	for (size_t i = 0; i < numberOfVehicles; i++)
	{
		if (strcmp(vehicles[i]->registration(), registration) == 0)
			return vehicles[i];
	}
	return nullptr;
}
