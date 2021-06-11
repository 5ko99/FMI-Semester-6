//
// Created by pgpetrov on 19.05.21 Рі..
//

#include <ostream>
#include <utility>
#include <iomanip>
#include "Person.h"
#include "Vehicle.h"
Vehicle::Vehicle(VehicleId registration, std::string description) :
    registration_(registration), description_(std::move(description)), owner_(nullptr) {
}
Vehicle::Vehicle(VehicleId registration, std::string  description, Person *owner) :
    registration_(registration), description_(std::move(description)), owner_(owner) {
}
bool Vehicle::operator==(const Vehicle &other) {
  return this->registration_ == other.registration_;
}
void Vehicle::set_owner(Person *owner) {
  this->owner_ = owner;
}
VehicleId Vehicle::registration() const {
  return registration_;
}
std::string Vehicle::description() const {
  return description_;
}
Person *Vehicle::owner() const {
  return owner_;
}
std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle) {
  vehicle.verbose_print(os);
  return os;
}
void Vehicle::concise_print(std::ostream &os) const {
  os << "registration: " << registration() << std::endl;
}
void Vehicle::verbose_print(std::ostream &os) const {
  os << "registration: " << registration() << std::endl;
  os << "owner: ";
  if (owner()) {
    os << std::endl;
    owner()->concise_print(os);
  } else {
    os << "non-existent" << std::endl;
  }
  os << "description: " << description() << std::endl;
}
void Vehicle::command_print(std::ostream &os) const {
  os << "VEHICLE " << registration() << " " << std::quoted(description()) << std::endl;
}
