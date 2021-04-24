#include "VehicleAllocator.h"

static Vehicle** nullptrArrayVehicles(std::size_t size)
{
	Vehicle** buf = new Vehicle*[size];
	for (std::size_t i = 0; i < size; ++i)
	{
		buf[i] = nullptr;
	}
	return buf;
}


VehicleAllocator::VehicleAllocator()
{
	vehicles = nullptrArrayVehicles(1);
	rawSize = 1;
	nextFreeIndex = 0;
}

VehicleAllocator::~VehicleAllocator()
{
	for (std::size_t i = 0; i < nextFreeIndex; ++i)
	{
		delete vehicles[i];
	}

	delete[] vehicles;
	printf("Cleaned the vehicles\n");
}

Vehicle * VehicleAllocator::allocate(const char * registration, const char * description, std::size_t space)
{
	if (nextFreeIndex >= rawSize)
	{
		expandBuffer();
	}
	Vehicle* veh = new Vehicle(registration, description, space);
	vehicles[nextFreeIndex++] = veh;
	return veh; // return vehicles[nextFreeIndex++] = new Vehicle(registration, description, space);
}

std::size_t VehicleAllocator::expansionFunction(std::size_t oldSize) const
{
	if (oldSize == 0) return 1;
	else return oldSize * 2;
}

std::size_t VehicleAllocator::expandBuffer()
{
	std::size_t newSize = expansionFunction(rawSize);
	Vehicle** newBuf = nullptrArrayVehicles(newSize);
	for (std::size_t i = 0; i < nextFreeIndex; ++i)
	{
		newBuf[i] = vehicles[i];
	}
	delete[] vehicles;
	vehicles = newBuf;
	rawSize = newSize;
	return newSize;
}
