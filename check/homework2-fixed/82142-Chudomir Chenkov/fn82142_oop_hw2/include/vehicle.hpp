#ifndef _VEHICLE_HPP_
#define _VEHICLE_HPP_

#include "registration.hpp"

#include <string>

class Person;

class Vehicle {

  public:
    Vehicle(const std::string &reg, const std::string &desc);

    std::string registration() const;
    std::string description() const;
    Person *owner() const;
    std::string to_string() const;

    void set_owner(Person *owner);

  private:
    Registration m_reg;
    std::string m_desc;
    Person *m_owner;
};

#endif // _VEHICLE_HPP_
