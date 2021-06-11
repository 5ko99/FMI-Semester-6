//
// Created by pgpetrov on 22.05.21 Рі..
//

#ifndef MIDKO__DATAMANAGER_H_
#define MIDKO__DATAMANAGER_H_

#include <vector>
#include "Person.h"

enum ObjectType
{
	VEHICLE, PERSON, INVALID
};

class DataManager
{
public:
	~DataManager();

	void addPerson(const std::string& name, unsigned int id);

	void addVehicle(const Registration& reg, const std::string& description);

	void acquire(unsigned int id, const Registration& reg);

	void release(unsigned int id, const Registration& reg);

	void removeVehicle(const Registration& reg);

	void removePerson(unsigned int id);

	void save(const std::string& path) const;

	std::string showPeople() const;

	std::string showVehicles() const;

	std::string showVehicle(const Registration& reg) const;

	std::string showPerson(unsigned int id) const;

	std::string showCommands() const;

	void readCommandsFrom(std::istream& inp);

	Person** findPerson(unsigned int id);

	Vehicle** findVehicle(const Registration& reg);

private:
	static ObjectType recognizeId(std::string id);

	std::vector<Person*> people;
	std::vector<Vehicle*> vehicles;
};

#endif //MIDKO__DATAMANAGER_H_
