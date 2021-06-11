#include "person.h"

Person::Person(unsigned _id, string _name) : id(_id), name(_name) {}

unsigned Person::get_id() const { return id; }

bool Person::has_vehicles() const { return vehicles.size() > 0; }

void Person::acquire(Vehicle* vehicle) {
    if (vehicle->has_owner()) throw invalid_argument("Someone already owns the vehicle");

    vehicle->owner = this;
    vehicles.push_back(vehicle);
}

void Person::release(const Registration& registration) {
    for (unsigned i = 0; i < vehicles.size(); i++)
        if (vehicles[i]->get_registration() == registration) {
            vehicles[i]->owner = nullptr;
            vehicles.erase(vehicles.begin() + i);
            break;
        }
}

void Person::clear() {
    while (!vehicles.empty()) {
        vehicles.back()->owner = nullptr;
        vehicles.pop_back();
    }
}

void Person::save(fstream& file) const {
    file << "PERSON " << name << " " << id << endl;
    for (const Vehicle* v : vehicles)
        file << "ACQUIRE " << id << " " << v->get_registration() << endl;
}

void Person::print() const {
    cout << *this;
    for (unsigned i = 0; i < vehicles.size(); i++) cout << "\t" << *vehicles[i];
}

ostream& operator<<(ostream& os, const Person& p) {
    return os << p.id << " - " << p.name << endl;
}
