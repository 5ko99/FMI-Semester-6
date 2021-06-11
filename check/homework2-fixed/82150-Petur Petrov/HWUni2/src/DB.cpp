//
// Created by pgpetrov on 21.05.21 Рі..
//

#include <algorithm> // for std::find_if
#include <stdexcept>
#include "DB.h"

void DB::release_vehicle(PersonId owner_id, VehicleId vehicle_id) {
  auto& p = person(owner_id);
  auto& v = vehicle(vehicle_id); // declared separately for strong exception safety if they are not found
  p.disown_vehicle(vehicle_id);
  v.set_owner();
}
void DB::transfer_vehicle(PersonId owner_id, VehicleId vehicle_id) {
  auto& p = person(owner_id);
  auto& v = vehicle(vehicle_id);
  if (v.owner())
    v.owner()->disown_vehicle(vehicle_id);
  p.acquire_vehicle(v);
  v.set_owner(&p);
}
void DB::remove_person(PersonId person_id) {
  auto person_it = std::find_if(people.begin(), people.end(), [=](auto p) {
    return p.id() == person_id;
  });
  if (person_it == people.end()) {
    throw std::logic_error("Could not remove!"
                           "Person with id " + std::to_string(person_id) + " was not found.");
  }
  for (auto& v : person_it->owned_vehicles())
    v->set_owner();
  people.erase(person_it);
}
void DB::remove_vehicle(VehicleId vehicle_id) {
  auto vehicle_it = std::find_if(vehicles.begin(), vehicles.end(), [=](auto v) {
    return v.registration() == vehicle_id;
  });
  if (vehicle_it == vehicles.end()) {
    throw std::logic_error("Could not remove!"
                           "Vehicle with registration " + std::string(vehicle_id) + " was not found.");
  }
  if (vehicle_it->owner())
    vehicle_it->owner()->disown_vehicle(vehicle_id);
  vehicles.erase(vehicle_it);
}
void DB::add_person(const std::string &name, PersonId id) {
  try {
    person(id);
  } catch(std::logic_error&) {
    people.emplace_back(name, id);
    return;
  }
  throw std::logic_error("Person with the same id already exists in the database.");
}
void DB::add_vehicle(VehicleId id, const std::string& description) {
  try {
    vehicle(id);
  } catch (std::logic_error&) {
    vehicles.emplace_back(id, description);
    return;
  }
  throw std::logic_error("Vehicle with the same id already exists in the database.");
}

std::ostream &DB::show_vehicles(std::ostream &os) const {
  for (const auto& v : vehicles)
    v.concise_print(os);
  return os;
}
std::ostream &DB::show_people(std::ostream &os) const {
  for (const auto& p : people)
    p.concise_print(os);
  return os;
}
std::ostream &DB::show_all(std::ostream &os) const {
  for (auto& v : vehicles)
    v.command_print(os);
  for (auto& p : people)
    p.command_print(os);
  return  os;
}

Vehicle &DB::vehicle(VehicleId vehicle_id) {
  auto ret = std::find_if(vehicles.begin(), vehicles.end(), [=](auto v) {
    return v.registration() == vehicle_id;
  });
  if (ret == vehicles.end())
    throw std::logic_error("Vehicle with specified id was not found.");
  return *ret;
}
Person &DB::person(PersonId person_id) {
  auto ret = std::find_if(people.begin(), people.end(), [=](auto p) {
    return p.id() == person_id;
  });
  if (ret == people.end())
    throw std::logic_error("Person with specified id was not found.");
  return *ret;
}
const Vehicle &DB::vehicle(VehicleId vehicle_id) const {
  return const_cast<DB*>(this)->vehicle(vehicle_id);
}
const Person &DB::person(PersonId person_id) const {
  return const_cast<DB*>(this)->person(person_id);
}
