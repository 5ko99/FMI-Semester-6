/*
 * personfactory.cpp
 *
 *  Created on: 23.05.2021 Рі.
 *      Author: plamen
 */

#include "personfactory.h"

#include <cassert>
#include <exception>
#include <stdexcept>

person_factory& person_factory::get_instance()
{
	static person_factory    instance; // Guaranteed to be destroyed.
										// Instantiated on first use.
	return instance;
}

person_factory::~person_factory()
{
	for(const auto &it : this->all_people)
	{
		delete it;
	}
}

Person* person_factory::create_person(unsigned int id, std::string name)
{
	Person tp(id, name);//Vehicle tv(reg, desc);
	auto it = this->all_people.find(&tp);
	if(it != this->all_people.end())
	{
		throw std::invalid_argument("Person with the same id already exists");
	}
	Person *p = new Person(id, std::move(name));
	try
	{
		this->all_people.insert(p);
	} catch (...)
	{
		delete p;
		throw;
	}
	return p;
}

Person* person_factory::get(unsigned int id) const
{
	Person tp(id, std::string(""));
	auto it = this->all_people.find(&tp);
	if(it == this->all_people.end())
	{
		throw std::invalid_argument("Person with this id does not exist");
	}
	return *it;
}

void person_factory::remove(Person* p)
{
	assert(p != nullptr);
	auto it = this->all_people.find(p);
	if(it == this->all_people.end())
	{
		throw std::invalid_argument("This Person does not exist");
	}
	assert(p == *it);
	this->all_people.erase(it); // this should not throw
	delete p;
}

void person_factory::remove(unsigned int id)
{
	Person tp(id, std::string(""));
	auto it = this->all_people.find(&tp);
	if(it == this->all_people.end())
	{
		throw std::invalid_argument("Person with this id does not exist");
	}
	Person *p = *it;
	this->all_people.erase(it); // this should not throw
	delete p;
}
