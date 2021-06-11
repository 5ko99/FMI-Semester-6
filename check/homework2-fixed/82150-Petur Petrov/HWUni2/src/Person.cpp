//
// Created by pgpetrov on 19.05.21 Рі..
//

#include <ostream>
#include <algorithm> // for std::find_if
#include <iomanip>
#include "Person.h"
#include "Vehicle.h"
PersonId Person::id() const {
  return id_;
}
std::string Person::name() const {
  return name_;
}
void Person::disown_vehicle(VehicleId registration) {
  auto to_delete = std::find_if(owned_vehicles_.begin(), owned_vehicles_.end(), [=](auto el) {
    return el->registration() == registration;
  });
  if (to_delete == owned_vehicles_.end()) {
    throw std::logic_error(
        "No vehicle with matching registration to " + std::string(registration) + " has been found!");
  }
  std::swap(*to_delete, owned_vehicles_.back());
  owned_vehicles_.pop_back();
}
bool Person::operator==(const Person &other) const {
  return id_ == other.id_;
}
void Person::acquire_vehicle(Vehicle &vehicle) {
  auto match = std::find_if(owned_vehicles_.begin(), owned_vehicles_.end(), [=](auto el) {
    return el->registration() == vehicle.registration();
  });
  if (match != owned_vehicles_.end()) {
    throw std::logic_error(
        "There is already a vehicle with a matching registration: " + std::string(vehicle.registration()));
  }
  owned_vehicles_.push_back(&vehicle);
}
const std::vector<Vehicle *> &Person::owned_vehicles() const {
  return owned_vehicles_;
}

std::ostream &operator<<(std::ostream &os, const Person &person) {
  person.verbose_print(os);
  return os;
}
void Person::concise_print(std::ostream &os) const {
  os << "name: " << name() << std::endl;
  os << "id: " << id() << std::endl;
}
void Person::verbose_print(std::ostream &os) const {
  os << "name: " << name() << std::endl;
  os << "id: " << id() << std::endl;
  os << "number of owned vehicles: " << owned_vehicles().size() << std::endl;
  for (Vehicle *v : owned_vehicles()) {
    os << "owned vehicle: ";
    v->concise_print(os);
  }
}
void Person::command_print(std::ostream &os) const {
  os << "PERSON " << std::quoted(name()) << " " << id() << std::endl;
  for (auto v : owned_vehicles()) {
    os << "ACQUIRE " << id() << " " << v->registration() << std::endl;
  }
}
