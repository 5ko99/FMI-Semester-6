#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED


class Vehicle;

#include <iostream>
#include <vector>

class Person
{
public:
	Person(std::string name, unsigned int uniqueId);
	void AcquireVehicle(Vehicle* vehicle);
	void ReleaseVehicle(Vehicle* vehicle);
	void ReleaseAllVehicles();
	std::string Print();

	std::string name;
	unsigned int uniqueId;
	std::vector<Vehicle*> vehicles;
};

#endif // !PERSON_H_INCLUDED
