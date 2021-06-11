#pragma once
#include "Person.h"
#include "Vehicle.h"
#include <vector>
#include <fstream>
class PersonAndVehicleManager
{
	std::vector<Person> persons;
	std::vector<Vehicle> vehicles;

	bool checkForNewVehicle(const char* registration) const;
	bool checkForNewPerson(unsigned int personId) const;

	bool validRegistration(const std::string& registration);
	
	
public:
	PersonAndVehicleManager();

	Person* newPerson(unsigned int personId, const char* personName);
	Vehicle* newVehicle(const char* registration, const char* description);
	void givePersonSingleVehicle(unsigned int personId, std::string registration);
	void removeVehicleFromPerson(unsigned int personId, std::string registration);
	void deletePerson(unsigned int personId);
	void deleteVehicle(std::string registration);
	Vehicle* findVehicle(std::string registration);
	Person* findPerson(unsigned int personId);
	const std::vector<Person>& getAllPersons() const;	
	const std::vector<Vehicle>& getAllVehicles() const;
};
