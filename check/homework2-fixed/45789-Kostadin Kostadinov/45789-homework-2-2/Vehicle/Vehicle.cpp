#include "Vehicle.hpp"

Vehicle::Vehicle(Registration& number, std::string desc) : number(number), desc(desc), owner(nullptr) {}

bool Vehicle::operator==(const Vehicle& rhs)const {
    if(this->number == rhs.number) return true;
    return false;
}

Registration Vehicle::getReg() const {
    return number;
}
Person* Vehicle::getOwner() const {
    return owner;
}

void Vehicle::setOwner(Person* owner) {
    this->owner = owner;
}

void Vehicle::removeOwner() {
    owner = nullptr;
}

void Vehicle::print() {
    std::cout << number << ' ' << desc;
}

void Vehicle::printAll() {
    std::cout << number << ' ' << desc;
    if (owner) {
        std::cout << ' ' << '[';
        owner->print();
        std::cout << ']';
    }
    std::cout << '\n';
}
