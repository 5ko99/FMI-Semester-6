//
// Created by pgpetrov on 21.05.21 Рі..
//

#ifndef HWUNI2_SRC_DB_H_
#define HWUNI2_SRC_DB_H_

#include <string>
#include <vector>
#include <list>
#include "Person.h"
#include "Vehicle.h"

class DB {
 public:
  std::ostream& show_all(std::ostream& os) const;
  std::ostream& show_people(std::ostream& os) const;
  std::ostream& show_vehicles(std::ostream& os) const;
  void add_vehicle(VehicleId vehicle_id, const std::string& description);
  void add_person(const std::string& name, PersonId id);
  void remove_vehicle(VehicleId vehicle_id);
  void remove_person(PersonId person_id);
  void transfer_vehicle(PersonId owner_id, VehicleId vehicle_id);
  void release_vehicle(PersonId owner_id, VehicleId vehicle_id);
  Vehicle& vehicle(VehicleId vehicle_id);
  Person& person(PersonId person_id);
  const Vehicle& vehicle(VehicleId vehicle_id) const;
  const Person& person(PersonId person_id) const;
 private:
  std::list<Vehicle> vehicles; // std::list to preserve element location
  std::list<Person> people;
};

#endif //HWUNI2_SRC_DB_H_
