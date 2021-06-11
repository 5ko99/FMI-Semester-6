#pragma once
#include <vector>
#include <string>
#include <cstddef>
#include "Registration.h"
#include "Vehicle.h"
#include "Person.h"

class Database {
	std::vector<Vehicle*> m_vehicles;
	std::vector<Person*> m_owners;
	std::vector<std::string> m_commands;
public:
	Database();
	Database(const std::string& filePath);
	~Database();
	void executeCommand(const std::string& line,bool readFromFile = 0);
	void addVehicle(const Registration& reg, const std::string& description);
	void addPerson(const std::string& name, unsigned int id);
	void acquire(unsigned int ownerId, const Registration& vehicleId) const;
	void release(unsigned int ownerId, const Registration& vehicleId) const;
	void removePerson(unsigned int ownerId);
	void removeVehicle(const Registration& vehicleId);
	void saveData(const std::string& filePath) const;
	std::size_t numberOfPeople() const;
	Person* getPerson(std::size_t index) const;
	std::size_t numberOfVehicles() const;
	Vehicle* getVehicle(std::size_t index) const;
	void printOwners() const;
	void printVehicles() const;
	void printPerson(unsigned int ownerId) const;
	void printVehicle(const Registration& reg) const;
private:
	Vehicle* findVehicle(const Registration& reg) const;
	Person* findPerson(unsigned int id) const;
	void deletePerson(const Person* p);
	void deleteVehicle(const Vehicle* v);
};
