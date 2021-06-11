#pragma once
#include "Person.h";
#include "Vehicle.h";
#include <vector>;
#include <string>;

class Database
{
	std::vector<Person> people;
	std::vector<Vehicle> vehicles;

	Person* findByID(unsigned int id);
	Vehicle* findByID(const Registration& id);
	bool isUnique(const Registration& vehicle_id); //TODO: Exception shit
	bool isUnique(unsigned int person_id);
	void functionCaller(std::vector<std::string>& arguments);

public:
	Database();
	Database(std::string& fileName);
	void addVehicle(const Registration& registration, std::string description);
	void addPerson(std::string name, unsigned int id);
	void acquire(unsigned int person_id, const Registration& vehicle_id);
	void release(unsigned int person_id, const Registration& vehicle_id);
	bool tryRemove(const Registration& vehicle_id); // add "yes", remove case sensitivity, add failure option
	bool tryRemove(unsigned int person_id);
	void showPeople() const;
	void showVehicles() const;
	bool tryShow(const Registration& vehicle_id);
	bool tryShow(unsigned int person_id);
	void save(std::string fileName);
};

