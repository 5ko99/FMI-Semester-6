#include <vector>

#include <string>

#include "PersonVehicles.h"
#include "Utils.h"

using namespace std;

Person::Person(const string& name, unsigned id) : name(name)
{
	this->id = id;
}

void Person::acquire(Vehicle& vehicle)
{
	vehicle.addOwner(*this);
}

void Person::add(Vehicle& vehicle)
{
	this->vehicles.push_back(&vehicle);;
}

void Person::releaseVehicle(Vehicle& vehicle)
{
	if (find(this->vehicles.begin(), this->vehicles.end(), &vehicle) == this->vehicles.end())
		return;
	vehicle.releaseOwner();
}

void Person::remove(Vehicle& vehicle)
{
	this->vehicles.erase(std::remove(this->vehicles.begin(), this->vehicles.end(), &vehicle), this->vehicles.end());
}

string Person::toString() const
{

	return "PERSON " + strToQuoted(this->getName()) + " " + to_string(this->getId());
}

string Person::toStringOwnedVehicles() const
{
	const size_t n = this->vehicles.size();
	string info;


	for (size_t i = 0; i < n; i++)
	{
		info += this->vehicles[i]->toString() + "\n";

	}

	return info;
}

string Person::getName() const
{
	return name;
}

unsigned int Person::getId() const
{
	return id;
}

vector<Vehicle*>* Person::getVectorOfVehicles()
{
	return &vehicles;
}
bool Person::operator==(const Person& person) const
{
	return this->name == person.name && this->id == person.id && this->vehicles == person.vehicles;
}
