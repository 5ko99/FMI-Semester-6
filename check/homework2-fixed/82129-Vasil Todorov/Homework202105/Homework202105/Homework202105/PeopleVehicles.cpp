#include <vector>
#include <stdexcept>
#include <string>

#include "Utils.h"
#include "PersonVehicles.h"

using namespace std;

void PeopleVehicles::createPerson(const string& name, unsigned int id)
{
	if (this->isPersonIdInDatabase(id))
		throw invalid_argument("");
	people.emplace_back(name, id);
}

void PeopleVehicles::createVehicle(const Registration& registration, const string& description)
{
	if (this->isVehicleRegInDatabase(registration))
		throw invalid_argument("");
	vehicles.emplace_back(registration, description);
}

bool PeopleVehicles::isPersonIdInDatabase(unsigned int personId) const
{
	const size_t n = this->people.size();
	for (size_t i = 0; i < n; i++)
	{
		if (this->people[i].getId() == personId)
		{
			return true;
		}
	}
	return false;
}

bool PeopleVehicles::isVehicleRegInDatabase(const Registration& reg) const
{
	const size_t n = this->vehicles.size();
	for (size_t i = 0; i < n; i++)
	{
		if (this->vehicles[i].getReg() == reg)
		{
			return true;
		}
	}
	return false;
}

string PeopleVehicles::toStringPeople() const
{
	const size_t n = this->people.size();
	string info;

	for (size_t i = 0; i < n; i++)
	{
		info += this->people[i].toString() + "\n";
	}


	return info;
}

string PeopleVehicles::toStringVehicles() const
{
	const size_t n = this->vehicles.size();
	string info;

	for (size_t i = 0; i < n; i++)
	{
		info += this->vehicles[i].toString() + "\n";

	}

	return info;
}

Vehicle* PeopleVehicles::findVehicle(const Registration& reg)
{
	const size_t n = this->vehicles.size();
	for (size_t i = 0; i < n; i++)
	{
		if (reg.getReg() == vehicles[i].getStringReg())
		{
			return &vehicles[i];
		}
	}
	return nullptr;

}

Person* PeopleVehicles::findPerson(unsigned int id)
{
	const size_t n = people.size();
	for (size_t i = 0; i < n; i++)
	{
		if (id == people[i].getId())
		{
			return &people[i];
		}
	}
	return nullptr;

}

id_type PeopleVehicles::getFormatType(const string& id)
{
	const size_t n = id.length();
	int result = true;
	for (size_t i = 0; i < n; i++)
	{
		if (!isDigit(id[i]))
		{
			result = false;
			break;
		}
	}

	if (result)
	{
		return id_type::id_person;
	}

	result = result || ((n == 8 && isLetter(id[0]) && isLetter(id[1]) && isDigit(id[2]) && isDigit(id[3]) && isDigit(id[4]) && isDigit(id[5]) && isLetter(id[6]) && isLetter(id[7]))
		|| (n == 7 && isLetter(id[0]) && isDigit(id[1]) && isDigit(id[2]) && isDigit(id[3]) && isDigit(id[4]) && isLetter(id[5]) && isLetter(id[6])));

	if (result)
	{
		return id_type::id_reg;
	}

	return id_type::id_invalid;
}


vector<Vehicle>* PeopleVehicles::getVectorOfVehicles()
{
	return &vehicles;
}

bool PeopleVehicles::removeVehicle(const Registration& reg)
{
	Vehicle* vehicle = findVehicle(reg);
	if (vehicle != nullptr)
	{
		vehicle->releaseOwner();
		this->vehicles.erase(remove(this->vehicles.begin(), this->vehicles.end(), *vehicle), this->vehicles.end());
		return true;
	}
	return false;
}

void PeopleVehicles::removePerson(unsigned int id)
{
	Person* person = findPerson(id);
	vector<Vehicle*>* vehiclesVecPtr = person->getVectorOfVehicles();
	size_t n = person->getVectorOfVehicles()->size();
	for (size_t i = 0; i < n; i++)
	{
		(*vehiclesVecPtr)[i]->releaseOwner();
	}
	this->people.erase(remove(this->people.begin(), this->people.end(), *person), this->people.end());
}
