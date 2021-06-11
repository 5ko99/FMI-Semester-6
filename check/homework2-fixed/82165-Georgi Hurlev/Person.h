#include <vector>
#include "Registration.h"

#ifndef PERSON_H
#define PERSON_H
#endif // !PERSON_H
class Vehicle;
#ifndef VEH_H
#include"Vehicle.h"
#endif // !VEH_H




class Person {
private:
	std::string name;
	unsigned int ID;
	//size_t numOfVehicles=0;
	std::vector <Vehicle*> vehicles;

	//bool allocateMemory();
	//bool deallocateMemory();
	bool doesntOwn(const Vehicle& veh) const;

	int findVehicle(const std::string& id) const;
public:
	Person(std::string name,unsigned int ID);
	Person(const Person&) = delete;
	Person(Person&& other) noexcept;
	~Person();
	void removeAllVehicles();//removes owners as well
	unsigned getId() const;
	size_t getOwnedVehNum() const;
	std::string getName()const;
	void addVehicle(Vehicle& veh);//adds owner as well
	void removeVehicle(const std::string& id);
	void printFullInfo(std::ostream& os) const;
	void printPersonalInfo(std::ostream& os) const;
	void outputAsCommand(std::ostream& os)const;
	bool operator==(const Person& other) const;
	Person& operator=(Person&& other) noexcept;
	friend class Vehicle;
};
