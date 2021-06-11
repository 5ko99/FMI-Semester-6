#ifndef _DATABASE_MANAGER_HPP_
#define _DATABASE_MANAGER_HPP_

#include "person.hpp"
#include "vehicle.hpp"

#include <vector>

class DatabaseManager {
  public:
    DatabaseManager()=default;
    ~DatabaseManager();

    void add_person(unsigned int id, const std::string &name);
    void add_vehicle(const std::string &reg, const std::string &desc);
    void remove_person(unsigned int id);
    void remove_vehicle(const std::string &reg);

    void acquire(unsigned int id, const std::string &reg);
    void release(unsigned int id, const std::string &reg);

    Person *get_person(unsigned int id);
    const Person *get_person(unsigned int id) const;

    Vehicle *get_vehicle(const std::string &reg);
    const Vehicle *get_vehicle(const std::string &reg) const;

    std::vector<Person*> get_people() const;
    std::vector<Vehicle*> get_vehicles() const;

  private:
    std::vector<Person*> m_people;
    std::vector<Vehicle*> m_vehicles;
};

#endif // _DATABASE_MANAGER_HPP_
