//
// Created by pgpetrov on 22.05.21 Рі..
//

#ifndef MIDKO__PERSON_H_
#define MIDKO__PERSON_H_

#include <vector>
#include <string>
#include "Vehicle.h"
#include "Registration.h"

class Person
{
public:
	Person(std::string name, unsigned int id);

	std::string getName() const;

	unsigned int getId() const;

	std::vector<Vehicle*> getVehicles() const;

	void addVehicle(Vehicle* vehicle);

	void removeVehicle(Registration registration);

	std::string getString() const;

	std::string getDetailedString() const;

	std::string getCommands() const;

private:
	std::string name;
	unsigned int id;
	std::vector<Vehicle*> vehicles_data;
};

#endif //MIDKO__PERSON_H_
