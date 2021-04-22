#include <cstddef>
#include "Vehicle.h"
#ifndef GARAGE_H
#define GARAGE_H
class Garage
{
	std::size_t capacity;
	int availableSpots;
	size_t storedVehiclesCount;
	Vehicle** vehicleData;

	//CREATE A DATA VARIABLE (ARRAY) TO STORE THE VEHICLES
public:
	Garage(std::size_t size); //Creates a garage with maximum 'size' capacity
	Garage(const Garage& otherGarage); //Copy constructor
	~Garage(); //Destructor

	void insert(Vehicle& v); //Adds a vehicle to the garage. If the operation doesn't succed it throws an exception //STRONG EXCEPTION GUARANTEE

	void erase(const char* registration); //Removes the car with the given registration


	const Vehicle& at(std::size_t pos) const; //Access to element at 'pos' position. If there's no such element throw an exception (std::out_of_range.)
	const Vehicle& operator[](std::size_t pos) const; //Access to element at 'pos' position

	bool empty() const; //Checks if the garage is empty

	std::size_t size() const; //Returns the number of vehicles in the garage

	void clear(); //Empties the garage from all the vehicles. The capacity is not changed

	const Vehicle* find(const char* registration) const; //Finds and returns the vehicle with the given registration
};

#endif GARAGE_H