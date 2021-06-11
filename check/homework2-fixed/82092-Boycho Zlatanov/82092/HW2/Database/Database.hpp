#ifndef Database_H
#define Database_H

#include <iostream>
#include <string>
#include <vector>
#include "../Person/Person.hpp"
#include "../Vehicle/Vehicle.hpp"

class Datebase
{
public:
  Datebase();
  ~Datebase();
  void vehicle(const std::string &, const std::string &);
  void person(const std::string &, const unsigned int &);
  void acquire();
  void release();
  void remove(const std::string &);
  void save();

private:
  void findPerson(const unsigned int &);
  void findVehicle(const std::string &);

  void removePerson(const unsigned int &);
  void removeVehicle(const std::string &);

  void showPeople();
  void showID();
  void showVehicles();

  void serialize(std::ofstream &);

  std::vector<Person> people;
  std::vector<Vehicle> cars;
};

#include "Database.cpp"
#endif
