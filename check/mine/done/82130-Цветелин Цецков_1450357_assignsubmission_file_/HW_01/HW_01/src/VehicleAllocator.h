#pragma once

#include "Vehicle.h"
#include <cstddef>

class VehicleAllocator
{
public:
	// ??????? ?????? ????????
	VehicleAllocator();

	VehicleAllocator(const VehicleAllocator& other) = delete;

	VehicleAllocator& operator=(const VehicleAllocator& other) = delete;

	// ????????? ????????? ? ??????????? ?????????? ?? ???? ??????
	// (?.?. ?????? ?? ?? ???? ?????????? ?? ??????
	// ????????? ?? ??????? ??????)
	~VehicleAllocator();

	/*
	Allocates a new vehicle on the heap.
	Can throw if the allocator is denied memory
	*/
	Vehicle* allocate(const char* registration, const char* description, std::size_t space);
private:
	Vehicle** vehicles;
	std::size_t rawSize;
	std::size_t nextFreeIndex;

	std::size_t expansionFunction(std::size_t oldSize) const;
	std::size_t expandBuffer();
};

/*
Defines a variable called vehicleAllocator. 
You should use the supplied allocator in order to create new Vehicles
*/
#define VEHICLE_LIFETIME(block) {\
VehicleAllocator vehicleAllocator;\
block;\
}
