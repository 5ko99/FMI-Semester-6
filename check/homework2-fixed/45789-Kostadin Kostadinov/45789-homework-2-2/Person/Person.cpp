#include "Person.hpp"
  
std::size_t Person::findVehicleIndex(Vehicle& veh) {
    for(size_t i = 0; i < list.size(); i++) {
        if (*list[i] == veh) return i;
    }
    return list.size();
}

Person::Person(std::string name, unsigned uuid) {
    this->name = name;
    this->uuid = uuid;
}

bool Person::operator==(const Person& rhs) const {
    return this->uuid == rhs.uuid;
}

unsigned Person::getUUID() const {
    return uuid;
}

Vehicle* Person::getVehicleAtInd(size_t ind) const {
    assert(ind >= 0 && ind < list.size() && "Invalid number");
    return list[ind];
}

size_t Person::vehicleCount() const {
    return list.size();
}

void Person::addVehicle(Vehicle& veh) {
    std::size_t index = findVehicleIndex(veh);
    if(index < list.size()) throw std::invalid_argument("Vehicle already exists!");
    list.push_back(&veh);
}

void Person::removeVehicle(Vehicle& veh) {
    std::size_t index = findVehicleIndex(veh);
    if(index == list.size()) throw std::invalid_argument("Vehicle not found!");
    list.erase(list.begin() + index);
}

void Person::removeAllVehicles() {
    list.clear();
}

void Person::print() {
    std::cout << name << ' ' << uuid;
}

void Person::printAll() {
    std::cout << name << ' ' << uuid;
    if (!list.empty()) {
        std::cout << " [\n";
        for (size_t i = 0; i < list.size(); i++) {
            list[i]->print();
            std::cout << '\n';
        }
        std::cout << ']';
    }
    std::cout << '\n';
}
