#ifndef Vehicle_H
#define Vehicle_H
#include <iostream>
#include <cstring>
#include <fstream>
#include "../Registration/Registartion.hpp"
#include "../Person/Person.hpp"

class Vehicle

{
public:
  Vehicle();
  Vehicle(const Vehicle &other);
  Vehicle(const Registration &, const std::string &, const Person &);
  ~Vehicle();
  Vehicle &operator=(const Vehicle &other);

  void removeOwner();
  void addOwner();
  void getNumberPlate() const;

  bool hasOwner() const;
  void serialize(std::ofstream&);

private:
  Registration numPlate;
  std::string description;
  Person *owner;
};

#include "Vehicle.cpp"
#endif
