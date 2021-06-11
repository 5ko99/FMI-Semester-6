#ifndef _PERSON_HPP_
#define _PERSON_HPP_

#include "vehicle.hpp"

#include <string>
#include <vector>

class Vehicle;

class Person {

  public:
    Person(unsigned int uid, const std::string &name);

    unsigned int uid() const;
    std::string name() const;
    std::vector<Vehicle *> vehicles() const;
    std::size_t vehicles_count() const;
    std::string to_string() const;

    void clear_vehicles();

    friend void Vehicle::set_owner(Person *owner);

  private:
    void add_vehicle(Vehicle *v);
    void remove_vehicle(Vehicle *v);

  private:
    unsigned int m_uid;
    std::string m_name;
    std::vector<Vehicle *> m_vehicles;
};

#endif // _PERSON_HPP_
