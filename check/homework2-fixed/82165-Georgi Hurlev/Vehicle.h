#ifndef VEH_H

#define VEH_H
#endif // !VEH_H
class Person;
#ifndef PERSON_H
#include"Person.h"
#endif


class Vehicle {
private:
	Registration registration;
	std::string description;
	Person* owner = nullptr;

public:
	Vehicle(const Registration registration, std::string description);
	Vehicle(Vehicle&& other) noexcept;
	Vehicle(const Vehicle&) = delete;
	~Vehicle() = default;

	void addOwner(Person& person);
	void removeOwner(bool toRemoveVehicle = false);
	bool hasOwner() const;
	std::string getDescrpt() const;
	std::string getRegistration() const;
	void printFullInfo(std::ostream& os)const;
	void printSpecifications(std::ostream& os) const;
	bool operator==(const Vehicle& other) const;
	Vehicle& operator=(Vehicle&& other) noexcept;
	void outputAsCommand(std::ostream& os)const;
};
