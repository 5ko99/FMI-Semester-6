#ifndef PERSON_H
#define PERSON_H
#include "../Vehicle/Vehicle.hpp"
#include <string>
#include <vector>
#include <cassert>

class Vehicle;

class Person {
public:
	Person() = delete;
	Person(std::string name, unsigned uuid);

	bool operator==(const Person& rhs) const; 

	unsigned getUUID() const;
	Vehicle* getVehicleAtInd(size_t ind) const;
	size_t vehicleCount() const;

	void addVehicle(Vehicle& veh);
	void removeVehicle(Vehicle& veh);
	void removeAllVehicles();

	void print();
	void printAll();

private:
	std::string name;
	unsigned uuid;
	std::vector<Vehicle*> list;

	std::size_t findVehicleIndex(Vehicle& veh);
};
#endif
