#include "vehicle.h"

Vehicle::Vehicle(const Registration& _registration, string _description)
    : registration(_registration), description(_description) {}

const Registration& Vehicle::get_registration() const { return registration; }

bool Vehicle::has_owner() const { return owner; }

Person* Vehicle::get_owner() const { return owner; }

void Vehicle::print() const {
    cout << registration << " - " << description << endl;
    if (has_owner()) cout << "\t" << *owner;
}

ostream& operator<<(ostream& os, const Vehicle& v) {
    return os << v.registration << " " << v.description << endl;
}
