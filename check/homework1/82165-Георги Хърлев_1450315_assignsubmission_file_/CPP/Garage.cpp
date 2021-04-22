#include <iostream>
#include <cassert>
#include "Garage.h"


bool Garage::allocateMemory(size_t newSize, Vehicle**& arr) const {
	try {
		arr = new Vehicle * [newSize];
	}
	catch (std::exception& e)
	{
		return false; //could not allocate
	}
	return true; //successful
}

Garage::Garage() :capacity(0), numCars(0), maxCars(0),vehicles(nullptr) //used in Program
{
}

Garage::Garage(size_t size) :capacity(size), numCars(0), maxCars(2) {
	if (size < 2)
	{
		maxCars = size;
	}
	if (!allocateMemory(maxCars, vehicles)) //Not enough memory to allocate for that many vehicles
	{
		capacity = 0;
		vehicles = nullptr;
		maxCars = 0;
		throw - 1;
	}
	
	nullifyAll();

	/* We can allocate memory for (size) number of vehicles as that's the maximum number of vehicles ,
	however , assuming that pointers take plenty of memory , we can allocate memory just for
	a few and allocate more later if needed .*/
}

Garage::Garage(Garage&& newGarage) noexcept {
	
	capacity = newGarage.capacity;
	numCars = newGarage.numCars;
	maxCars = newGarage.maxCars;
	vehicles = newGarage.vehicles;

	newGarage.capacity = newGarage.numCars = newGarage.maxCars = 0;
	newGarage.vehicles = nullptr;

}

void Garage::nullifyAll() {
	for (size_t i = 0; i < maxCars; i++)
	{
		vehicles[i] = nullptr;
	}
}


size_t Garage::findTotalCapacity(const Garage& newGarage) {
	size_t cap=newGarage.capacity; 
	size_t carNums = newGarage.size();
	size_t i = 0;
	while (carNums > 0)
	{
		if (&newGarage[i] != nullptr) //we found a car
		{
			carNums--;
			cap += newGarage[i].space();
			i += newGarage[i].space() - 1; //we skip the places that are already taken by that vehicle
			continue;
		}
		i++;
	}
	return cap;
}

Garage::Garage(const Garage& newGarage) {
	if (!allocateMemory(newGarage.maxCars, vehicles)) //Not enough memory to allocate for that many vehicles
	{
		
		capacity = 0;
		vehicles = nullptr;
		maxCars = 0;
		throw - 1;
	}
	
	capacity = newGarage.capacity;
	numCars = newGarage.numCars;
	maxCars = newGarage.maxCars;
	for (size_t i = 0; i < maxCars; i++)
	{
		vehicles[i] = newGarage.vehicles[i]; //pointing to the same vehicle memory adress as the new Garage
	}

}

Garage::~Garage() {
	delete[] vehicles;
	capacity = 0;
	numCars = 0;
	maxCars = 0;
	vehicles = nullptr;
}

void Garage::insert(Vehicle& v) {

	if (capacity < v.space()) //not enough space to park it 
	{
		throw 0;
	}
	const char* reg = v.registration();
	if (find(reg) != nullptr) //there is already such car in the garage
	{
		delete[] reg;
		throw 1;
	}
	delete[] reg;
	if (numCars == maxCars) //we have no free pointers 
	{
		Vehicle** newVehicles;
		if (!allocateMemory(maxCars + 1, newVehicles)) //not enough memory
		{
			throw - 1;
		}
		for (size_t i = 0; i < numCars; i++)
		{
			newVehicles[i] = vehicles[i];
		}
		delete[] vehicles;
		vehicles = newVehicles;
		vehicles[maxCars++] = nullptr;
	}

	vehicles[numCars++] = &v;
	capacity -= v.space();
}

void Garage::erase(const char* registration) {

	size_t br = 0;
	bool isFound = false;
	const char* regArr;
	while (!isFound && br < maxCars)
	{
		regArr = (*vehicles[br]).registration();/*registration uses c_str which allocates dynamic memory and has to be deleted*/
		isFound = (strcmp(regArr, registration) == 0);
		delete[] regArr;
		br++;
	}
	br--;
	if (!isFound) //no such vehicle
	{
		return;
	}
	capacity += (*vehicles[br]).space(); //freeing more space
	for (size_t i = br; i < numCars - 1; i++)//rearrange them
	{
		vehicles[i] = vehicles[i + 1];
	}
	vehicles[--numCars] = nullptr;
	
	
}

const Vehicle& Garage::at(std::size_t pos) const {
	if (pos >= numCars)
	{
		throw std::out_of_range("Invalid vehicle position.Out of range");
	}
	return *vehicles[pos];
}

const Vehicle* Garage::find(const char* registration) const {
	size_t br = 0;
	bool isFound = false;
	const char* regArr;
	while (!isFound && br < numCars)
	{
		regArr = (*vehicles[br]).registration();/*registration uses c_str which allocates dynamic memory and has to be deleted*/
		isFound = (strcmp(regArr, registration) == 0);
		delete[] regArr;
		br++;
	}
	if (!isFound) //no such vehicle
	{
		return nullptr;
	}

	return vehicles[br-1];
}

bool Garage::empty() const {
	return (numCars == 0);
}

std::size_t Garage::size() const {
	return numCars;
}

void Garage::clear()
{
	for (size_t i = 0; i < maxCars; i++)
	{
		if (vehicles[i] != nullptr)
		{
			capacity += (*vehicles[i]).space();
			vehicles[i] = nullptr;
		}
	}
	numCars = 0;
}


const Vehicle& Garage::operator[](std::size_t pos) const{
	assert(pos < numCars);
	return *vehicles[pos];
}


Garage& Garage::operator=(const Garage& newGarage) {
	if (&newGarage==this)
	{
		return *this;
	}
	if (!allocateMemory(newGarage.maxCars, vehicles)) //Not enough memory to allocate for that many vehicles
	{
		capacity = 0;
		vehicles = nullptr;
		maxCars = 0;
		throw - 1;
	}
	capacity = newGarage.capacity;
	numCars = newGarage.numCars;
	maxCars = newGarage.maxCars;
	for (size_t i = 0; i < maxCars; i++)
	{
		vehicles[i] = newGarage.vehicles[i]; //pointing to the same vehicle memory adress as the new Garage
	}
	return *this;
}

bool Garage::operator==(const Garage& other) const {//if the garage are ABSOLUTELY the same as vehicles and places
	//std::cout << "==\n";
	if (numCars!=other.numCars || maxCars!=other.maxCars)
	{
		
		return false;
	}
	size_t br = 0;
	//size_t numOfCars = numCars;
	while (br < maxCars )
	{
		if (!((*vehicles[br]) == other[br]))
		{
			return false;
		}
		br++;
	}
	return true;
	
}

Garage& Garage::operator=(Garage&& newGarage)noexcept {
	if (this != &newGarage)
	{
		delete[] vehicles;
		capacity = newGarage.capacity;
		numCars=newGarage.numCars;
		maxCars=newGarage.maxCars;
		vehicles = newGarage.vehicles;

		newGarage.capacity = newGarage.numCars = newGarage.maxCars = 0;
		newGarage.vehicles = nullptr;

	}
	return *this;
}

