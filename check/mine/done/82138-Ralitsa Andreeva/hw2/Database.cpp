#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstddef>
#include "Helpers.h"
#include "Vehicle.h"
#include "Person.h"
#include "Command.h"
#include "Database.h"

Database::Database(){}
Database::Database(const std::string& filePath)
{
	std::ifstream ifs(filePath);
	std::size_t i = 0;
	while (true)
	{
		std::string fileLine;
		std::getline(ifs, fileLine);
		if (ifs.eof())break;
		try {
			executeCommand(fileLine,1);
			i++;
		}
		catch (...) {
			std::string error = "Invalid command line " + std::to_string(i);
			throw std::invalid_argument(error);
		}
	}
	ifs.close();
}
Database::~Database()
{
	for (std::size_t i = 0; i < m_owners.size(); i++)
	{
		delete m_owners[i];
	}
	for (std::size_t i = 0; i < m_vehicles.size(); i++)
	{
		delete m_vehicles[i];
	}
}
void Database::executeCommand(const std::string& line,bool readFromFile)
{
	try {
		Command c(line);
		if (c.command() == "vehicle") {
			try {
				std::string description = c.secondArgument();
				Registration reg = c.convertToRegistration(1);
				addVehicle(reg, description);
			}
			catch (...) {
				throw;
			}
		}
		else if (c.command() == "person") {
			try {
				std::string name = c.firstArgument();
				unsigned int id = c.convertToUInt(2);
				addPerson(name,id);
			}catch(...) {
				throw;
			}
		}
		else if (c.command() == "acquire") {
			try {
				unsigned int ownerId = c.convertToUInt(1);
				Registration vehicleId = c.convertToRegistration(2);
				acquire(ownerId, vehicleId);
			}
			catch (...) {
				throw;
			}
		}
		else if (c.command() == "release") {
			try {
				unsigned int ownerId = c.convertToUInt(1);
				Registration vehicleId = c.convertToRegistration(2);
				release(ownerId, vehicleId);
			}
			catch (...) {
				throw;
			}
		}
		else if (c.command() == "remove") {
			unsigned int ownerId = c.convertToUInt(1);
			if (ownerId != 0) {
				Person* p = findPerson(ownerId);
				if (p->numberOfVehicles() != 0 && !readFromFile) {
					std::cout << "Are you sure you want to remove this person from the database?(yes/no)\n";
					std::string answer;
					std::cin >> answer;
					toLower(answer);
					if (answer == "yes")
						removePerson(ownerId);
				}
				else removePerson(ownerId);
			}
			else {
				try {
					Registration vehicleId = c.convertToRegistration(1);
					Vehicle* v = findVehicle(vehicleId);
					if (v->owner() != nullptr && !readFromFile) {
						std::cout << "Are you sure you want to remove this vehicle from the database?(yes/no)\n";
						std::string answer;
						std::cin >> answer;
						toLower(answer);
						if (answer == "yes") {
							removeVehicle(vehicleId);
						}
						else return;
					}
					else removeVehicle(vehicleId);
				}
				catch (...)
				{
					throw;
				}
			}
		}
		else if (c.command() == "save") {
			saveData(c.firstArgument());
		}
		else if (c.command() == "show") {
			if (c.firstArgument() == "PEOPLE")printOwners();
			else if (c.firstArgument() == "VEHICLES")printVehicles();
			else {
				try {
					unsigned id = c.convertToUInt(1);
					printPerson(id);
				}
				catch (...) {
					try {
						Registration reg = c.convertToRegistration(1);
						printVehicle(reg);
					}
					catch (...) {
						throw;
					}
				}
			}
		}
		if(c.command() != "show" && c.command() != "save")m_commands.push_back(line);
	}
	catch (const std::exception& e){
		std::cout << e.what() << std::endl;
	}
}
void Database::addVehicle(const Registration& reg, const std::string& description)
{
	try {
		Vehicle* v = new Vehicle(reg, description);
		m_vehicles.push_back(v);
	}
	catch (...) {
		throw;
	}
}
void Database::addPerson(const std::string& name, unsigned int id)
{
	try {
		Person* p = new Person(name, id);
		m_owners.push_back(p);
	}
	catch (...) {
		throw;
	}
}
void Database::acquire(unsigned int ownerId, const Registration& vehicleId) const
{
	Person* owner = findPerson(ownerId);
	if (owner == nullptr) {
		throw std::invalid_argument("Invalid owner id");
	}
	Vehicle* vehicle = findVehicle(vehicleId);
	if (vehicle == nullptr) {
		throw std::invalid_argument("Invalid registration");
	}
	owner->add(vehicle);
}
void Database::release(unsigned int ownerId, const Registration& vehicleId) const
{
	Person* owner = findPerson(ownerId);
	if (owner == nullptr) {
		throw std::invalid_argument("Invalid owner id");
	}
	Vehicle* vehicle = findVehicle(vehicleId);
	if (vehicle == nullptr) {
		throw std::invalid_argument("Invalid registration");
	}
	owner->remove(vehicle);
}
void Database::removePerson(unsigned int ownerId)
{
	Person* p = findPerson(ownerId);
	if (p == nullptr) {
		return;
	}
	if (p->numberOfVehicles() != 0) {
		p->removeAll();
	}
	deletePerson(p);
}
void Database::removeVehicle(const Registration& vehicleId)
{
	Vehicle* v = findVehicle(vehicleId);
	if (v == nullptr) {
		return;
	}
	if (v->owner() != nullptr) {
		v->owner()->remove(v);
	}
	deleteVehicle(v);
}
void Database::saveData(const std::string& filePath) const
{
	std::ofstream ofs(filePath);
	if (!ofs) {
		std::cout << "Can't open file!\n";
		return;
	}
	for (std::size_t i = 0; i < m_commands.size(); i++)
	{
		ofs << m_commands[i] << '\n';
	}
	ofs.close();
}
std::size_t Database::numberOfPeople() const
{
	return m_owners.size();
}
Person* Database::getPerson(std::size_t index) const
{
	return m_owners[index];
}
std::size_t Database::numberOfVehicles() const
{
	return m_vehicles.size();
}
Vehicle* Database::getVehicle(std::size_t index) const
{
	return m_vehicles[index];
}
void Database::printOwners() const
{
	for (std::size_t i = 0; i < m_owners.size(); i++)
	{
		std::cout << i + 1 << ". " << *(m_owners[i]) << "\n";
	}
}
void Database::printVehicles() const
{
	for (std::size_t i = 0; i < m_vehicles.size(); i++)
	{
		std::cout << i + 1 << ". " << *(m_vehicles[i]) << "\n";
	}
}
void Database::printPerson(unsigned int ownerId) const
{
	Person* p = findPerson(ownerId);
	if (p == nullptr) {
		std::cout << "No owner with id " << ownerId << std::endl;
		return;
	}
	std::cout << *p << "\n";
	p->printVehicles();
}
void Database::printVehicle(const Registration& reg) const
{
	Vehicle* v = findVehicle(reg);
	if (v == nullptr) {
		std::cout << "No vehicle with registration" << reg << std::endl;
		return;
	}
	std::cout << *v << "\n";
	if (v->owner() != nullptr)std::cout << "Owner: " << *(v->owner()) << "\n";
	else std::cout << "No owner\n";
}
Vehicle* Database::findVehicle(const Registration& reg) const
{
	for (std::size_t i = 0; i < m_vehicles.size(); i++)
	{
		if (m_vehicles[i]->plate() == reg)return m_vehicles[i];
	}
	return nullptr;
}
Person* Database::findPerson(unsigned int id) const
{
	for (std::size_t i = 0; i < m_owners.size(); i++)
	{
		if (m_owners[i]->id() == id)return m_owners[i];
	}
	return nullptr;
}
void Database::deletePerson(const Person* p)
{
	for (std::size_t i = 0; i < m_owners.size(); i++)
	{
		if (p == m_owners[i]) {
			m_owners.erase(m_owners.begin() + i);
			delete p;
			return;
		}
	}
}
void Database::deleteVehicle(const Vehicle* v)
{
	for (std::size_t i = 0; i < m_vehicles.size(); i++)
	{
		if (v == m_vehicles[i]) {
			m_vehicles.erase(m_vehicles.begin() + i);
			delete v;
			return;
		}
	}
	
}
