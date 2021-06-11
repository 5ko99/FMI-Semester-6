#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <stdexcept>
#include "Vehicle.h"
#include "Person.h"

std::vector<unsigned int> Person::usedId;

Person::Person(const std::string& name, unsigned int id) : m_id(id), m_name(name)
{
	if (used(id) == 1)throw std::invalid_argument("Id is taken");
	usedId.push_back(id);
}
Person::~Person()
{
	for (std::size_t i = 0; i < usedId.size(); i++)
	{
		if (m_id == usedId[i]) {
			usedId.erase(usedId.begin()+i);
			break;
		}
	}
}
unsigned int Person::id() const
{
	return m_id;
}
std::string Person::name() const
{
	return m_name;
}
void Person::add(Vehicle* v)
{
	if (v->m_owner != nullptr) {
		v->m_owner->remove(v);
	}
	v->m_owner = this;
	m_vehicles.push_back(v);
}
void Person::remove(Vehicle* v)
{
	if (v->m_owner != this)return;
	v->m_owner = nullptr;
	for (std::size_t i = 0; i < m_vehicles.size(); i++)
	{
		if (v == m_vehicles[i]) {
			m_vehicles.erase(m_vehicles.begin()+i);
			break;
		}
	}
}
bool Person::owns(const Vehicle* v) const
{
	return v->owner() == this;
}
std::size_t Person::numberOfVehicles() const
{
	return m_vehicles.size();
}
void Person::removeAll()
{
	for (std::size_t i = 0; i < m_vehicles.size(); i++)
	{
		m_vehicles[i]->m_owner = nullptr;
	}
	m_vehicles.clear();
}
void Person::printVehicles() const
{
	std::cout << "Vehicles:\n";
	for (std::size_t i = 0; i < m_vehicles.size(); i++)
	{
		std::cout << i + 1 << ". " << *(m_vehicles[i]) << "\n";
	}
}
std::ostream& operator<<(std::ostream& os, const Person& p)
{
	os << p.m_name << " " << p.m_id;
	return os;
}
bool Person::used(unsigned int id)
{
	for (std::size_t i = 0; i < usedId.size(); i++)
	{
		if (usedId[i] == m_id)return 1;
	}
	return 0;
}
