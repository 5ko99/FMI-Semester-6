#include "Person.h"

Person::Person(const std::string& name, const unsigned id)
{
	this->_name = name;
	this->_id = id;
}

std::string Person::name() const
{
	return _name;
}

 unsigned Person::id() const
{
	return _id;
}

 std::vector<Vehicle*>& Person::vehicles()
 {
	 return _vehicles;
 }
