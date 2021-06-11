//
// Created by pgpetrov on 22.05.21 Рі..
//

#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "Person.h"
Person::Person(std::string name, unsigned int id) : name(name), id(id){

}
std::string Person::getName() const {
  return name;
}
unsigned int Person::getId() const {
  return id;
}
std::vector<Vehicle *> Person::getVehicles() const {
  return vehicles_data;
}
//TODO: maybe causes bad_alloc
void Person::addVehicle(Vehicle *vehicle) {
  for (Vehicle* v : vehicles_data) {
    if (v->getRegistration() == vehicle->getRegistration()) {
      throw std::logic_error("vehicle with same registration already exists");
    }
  }
  vehicles_data.push_back(vehicle);
}
//TODO: maybe causes bad_alloc
void Person::removeVehicle(Registration registration) {
  for (std::size_t i=0; i < vehicles_data.size(); ++i) {
    if (vehicles_data[i]->getRegistration() == registration) {
      std::swap(vehicles_data[i], vehicles_data.back());
      vehicles_data.pop_back();
      return;
    }
  }
  throw std::logic_error(" cannot remove no such vehicle found");
}
std::string Person::getString()  const{
  std::ostringstream result;
  result << "name " << name << std::endl;
  result << "id " << id << std::endl;
  return result.str();
}
std::string Person::getCommands()  const{
  std::ostringstream result;
  result << "PERSON " << std::quoted(name) << " " << id << std::endl;
  for (Vehicle* v : vehicles_data) {
    result << "ACQUIRE " << id << " " << v->getRegistration().getData() << std::endl;
  }
  return result.str();
}
std::string Person::getDetailedString() const {
  std::ostringstream result;
  result << getString();
  if (!vehicles_data.empty()) {
    result << "vehicles: " << std::endl;
    for (Vehicle *v : vehicles_data) {
      result << v->getString();
    }
  }
  return result.str();
}
