#pragma once

#include <string>
#include <vector>

class Vehicle;

class Person
{
public:
	Person(const std::string& name, unsigned int uuid);
	~Person();

	bool aquire(Vehicle* veh);
	bool release(Vehicle* veh);
	bool owns(Vehicle* veh) const;

	unsigned int getUuid() const { return uuid; }
	const std::string& getName() const { return name; }
	const std::vector<Vehicle*>& getVehicles() const { return vehicles; }

	bool operator==(const Person& other) const;

	static const std::vector<unsigned int>& allUsedUUIDs() { return usedUuids; }
private:
	std::string name;
	unsigned int uuid;
	std::vector<Vehicle*> vehicles;

	static std::vector<unsigned int> usedUuids;

	bool uuidAlreadyInUse(const unsigned int uuid);
};

