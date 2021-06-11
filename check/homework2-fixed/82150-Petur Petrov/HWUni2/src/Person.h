//
// Created by pgpetrov on 19.05.21 Рі..
//

#ifndef HWUNI2_SRC_PERSON_H_
#define HWUNI2_SRC_PERSON_H_
#include <string>
#include <utility>
#include <vector>
#include "Vehicle.h"

typedef unsigned int PersonId;

class Person {
 public:
  Person(std::string name, PersonId id) : name_(std::move(name)), id_(id) {}
  void acquire_vehicle(Vehicle &vehicle);
  void disown_vehicle(VehicleId registration);
  const std::vector<Vehicle *> &owned_vehicles() const;
  std::string name() const;
  PersonId id() const;

  friend std::ostream &operator<<(std::ostream &os, const Person &person);
  void verbose_print(std::ostream &os) const;
  void concise_print(std::ostream &os) const;
  void command_print(std::ostream &os) const;
  bool operator==(const Person &other) const;
 private:
  std::string name_;
  PersonId id_;
  std::vector<Vehicle *> owned_vehicles_;
};

#endif //HWUNI2_SRC_PERSON_H_
