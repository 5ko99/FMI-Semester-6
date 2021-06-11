//
// Created by pgpetrov on 19.05.21 Рі..
//

#ifndef HWUNI2_SRC_VEHICLE_H_
#define HWUNI2_SRC_VEHICLE_H_
#include "Registration.h"

typedef Registration VehicleId;
class Person;
typedef unsigned int PersonId;

class Vehicle {
 public:
  Vehicle(VehicleId registration, std::string description);
  Vehicle(VehicleId registration, std::string description, Person *owner);
  void set_owner(Person *owner=nullptr);
  VehicleId registration() const;
  std::string description() const;
  Person *owner() const;

  friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle);
  void verbose_print(std::ostream& os) const;
  void concise_print(std::ostream& os) const;
  void command_print(std::ostream& os) const;
  bool operator==(const Vehicle &other);
 private:
  VehicleId registration_;
  std::string description_;
  Person *owner_;
};

#endif //HWUNI2_SRC_VEHICLE_H_
