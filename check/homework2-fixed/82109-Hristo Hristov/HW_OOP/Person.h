#pragma once
#include <string>
#include <vector>

class Vehicle; //Forward declaration of the class Vehicle (that's why "Vehicles.h" is missing)

class Person
{
private:
	std::string name;
	unsigned int id;
	std::vector<Vehicle*> vehiclesOwned;

public:
	static std::vector<Person*> people;
public:
	Person();
	Person(std::string newName, unsigned int newId);
	Person& operator=(const Person& other);
	~Person();

	void removePerson(int id);
//getters
	unsigned int getId();
	std::string getName();
	std::vector<Vehicle*> getVehiclesOwned();
	Person* getPersonById(int id);
//setters
	void removeOwnedVehicle(unsigned int index);
	void addVehicle(Vehicle *other);
//helper methods
private:
	void copy(const Person &other);
	

};

