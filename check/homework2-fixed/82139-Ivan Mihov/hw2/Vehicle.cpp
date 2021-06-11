

# include "Vehicle.h"
# include <stdexcept>
# include <iostream>
Vehicle::Vehicle(const Registration& reg, const std::string& Descr) {
    try { this->reg = reg; }
    catch (...) {
        throw;
    }
    this->descr = Descr;
    this->owned = false;
}
void Vehicle::setOwner(Person* other) {
    if (&this->per != &other) {
        this->per = other;
        this->owned = true;
    }
}
void Vehicle::eraseOwner() {
    if (this->owned) {
        this->per = nullptr;
        this->owned = false;
    }
}
std::string Vehicle::getRegistration() const {
    return this->reg.getRegistration();
}
std::string Vehicle::getDescription() const {
    return this->descr;
}
void Vehicle::setDesription(const std::string& descr) {
    this->descr = descr;
}
void Vehicle::setRegistration(const Registration& registration) {
    this->reg = registration;
}
void Vehicle::print() const {
    this->reg.print();
    std::cout << " " << this->descr << "\n";
}
bool Vehicle::isItOwned()const {
    return this->owned;
}
Person* Vehicle::getOwner()const {
    return this->per;
}
