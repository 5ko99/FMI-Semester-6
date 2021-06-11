#include "PersonAndVehicleManager.h"
#include <stdexcept>
#include <utility>
#include <fstream>

bool PersonAndVehicleManager::checkForNewVehicle(const char* registration) const
{
	for (std::size_t i = 0; i < this->vehicles.size(); i++)
	{
		if (this->vehicles[i].getRegistration().getRegistrationString() == std::string(registration))
		{
			return false;
			
		}
	}
	return true;
}
bool PersonAndVehicleManager::validRegistration(const std::string& registration)
{
	std::size_t size = registration.size();
	if (size > 8 || size < 7)
	{
		return false;
	}

	for (size_t i = 0; i < size - 6; i++)
	{
		if (registration[i] < 'A' || registration[i] > 'Z')
		{
			return false;
		}
	}

	for (size_t i = size - 6; i < size - 2; i++)
	{
		if (registration[i] < '0' || registration[i] > '9')
		{
			return false;
		}
	}

	for (size_t i = size - 2; i < size; i++)
	{
		if (registration[i] < 'A' || registration[i] > 'Z')
		{
			return false;
		}
	}

	return true;
}

bool PersonAndVehicleManager::checkForNewPerson(unsigned int personId) const
{
	for (std::size_t i = 0; i < this->persons.size(); i++)
	{
		if (this->persons[i].getId() == personId)
		{
			return false;
		}
	}
	return true;
}

Vehicle* PersonAndVehicleManager::findVehicle(std::string registration) 
{
	if (!validRegistration(registration))
	{
		throw std::runtime_error("Invalid registration number: " + registration);
	}

	for (size_t i = 0; i < vehicles.size(); i++)
	{
		if (vehicles[i].getRegistration().getRegistrationString() == registration)
		{
			return &this->vehicles[i];
		}
	}
	return nullptr;
}
Person* PersonAndVehicleManager::findPerson(unsigned int personId) 
{
	
	for (size_t i = 0; i < persons.size(); i++)
	{
		if (persons[i].getId() == personId)
		{
			return &persons[i];
		}
	}
	return nullptr;
}

PersonAndVehicleManager::PersonAndVehicleManager()
{
}

Person* PersonAndVehicleManager::newPerson(unsigned int personId, const char* personName)
{
	if (!checkForNewPerson(personId))
	{
		throw std::runtime_error("Person with that id already exists: " + std::to_string(personId));
	}

	persons.push_back(Person(personId, personName));
	
	return &persons[persons.size() - 1];
}

Vehicle* PersonAndVehicleManager::newVehicle(const char* registration, const char* description)
{
	if (!checkForNewVehicle(registration))
	{
		throw std::runtime_error("Vehicle with that registration number already exists: " + std::string(registration));
	}
	
	vehicles.push_back(Vehicle(registration, description));

	return &vehicles[vehicles.size() - 1];
}

void PersonAndVehicleManager::givePersonSingleVehicle(unsigned int personId, std::string registration) 
{
	Person* person = findPerson(personId);
	Vehicle* vehicle = findVehicle(registration);

	if (!person || !vehicle)
	{
		throw std::runtime_error("Couldn't find person or vehicle!");
	}

	if (vehicle->hasOwner())
	{
		removeVehicleFromPerson(vehicle->getOwner()->getId(), registration);
	}
	
	person->addVehicle(*vehicle);
	vehicle->setOwner(*person);
	
}

void PersonAndVehicleManager::removeVehicleFromPerson(unsigned int personId, std::string registration)
{
	Person* person = findPerson(personId);
	Vehicle* vehicle = findVehicle(registration);
	if (!person || !vehicle)
	{
		throw std::runtime_error("Couldn't find person or vehicle!");
	}
	person->removeVehicle(registration);
	vehicle->removeOwner();
	int a = 5;
}

void PersonAndVehicleManager::deletePerson(unsigned int personId)
{
	std::size_t sz = this->persons.size();
	for (std::size_t i = 0; i < sz; i++)
	{
		if (this->persons[i].getId() == personId)
		{
			std::size_t size = this->persons[i].getVehicles().size();
			for (size_t i = 0; i < size; i++)
			{
				removeVehicleFromPerson(personId, this->persons[i].getVehicles()[i]->getRegistration().getRegistrationString());
			}
			std::swap(this->persons[sz - 1], this->persons[i]);
			this->persons.pop_back();
			break;
		}
	}
}

void PersonAndVehicleManager::deleteVehicle(std::string registration)
{
	for (std::size_t i = 0; i < this->vehicles.size(); i++)
	{
		if (this->vehicles[i].getRegistration().getRegistrationString() == registration)
		{
			removeVehicleFromPerson(this->vehicles[i].getOwner()->getId(), registration);
			this->vehicles.erase(this->vehicles.begin() + i);
		}
	}
}

const std::vector<Person>& PersonAndVehicleManager::getAllPersons() const
{
	return this->persons;
}

const std::vector<Vehicle>& PersonAndVehicleManager::getAllVehicles() const
{
	return this->vehicles;
}
