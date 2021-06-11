#include "container.h"

Container::~Container() {
    for (Person* p : people) delete p;
    for (Vehicle* v : vehicles) delete v;
}

int Container::index_of(unsigned id) const {
    for (unsigned i = 0; i < people.size(); i++)
        if (people[i]->get_id() == id) return i;
    return -1;
}

int Container::index_of(const Registration& registration) const {
    for (unsigned i = 0; i < vehicles.size(); i++)
        if (vehicles[i]->get_registration() == registration) return i;
    return -1;
}

Person* Container::find(unsigned id) const {
    int index = index_of(id);
    if (index < 0) return nullptr;
    return people[index];
}

Vehicle* Container::find(const Registration& registration) const {
    int index = index_of(registration);
    if (index < 0) return nullptr;
    return vehicles[index];
}

bool Container::contains(unsigned id) const { return index_of(id) >= 0; }

bool Container::contains(const Registration& registration) const {
    return index_of(registration) >= 0;
}

bool Container::is_dependant(unsigned id) const {
    Person* p = find(id);
    if (!p) return false;
    return p->has_vehicles();
}

bool Container::is_dependant(const Registration& registration) const {
    Vehicle* v = find(registration);
    if (!v) return false;
    return v->has_owner();
}

void Container::push(unsigned int id, string name) {
    if (contains(id)) return;
    Person* p = new (nothrow) Person{id, name};
    if (!p) {
        cout << "Could not allocate person\n";
        return;
    }
    people.push_back(p);
}

void Container::push(const Registration& registration, const string& description) {
    if (contains(registration)) return;
    Vehicle* v = new (nothrow) Vehicle{registration, description};
    if (!v) {
        cout << "Could not allocate vehicle\n";
        return;
    }
    vehicles.push_back(v);
}

void Container::remove(unsigned id) {
    int index = index_of(id);
    if (index < 0) return;

    people[index]->clear();
    delete people[index];
    people.erase(people.begin() + index);
}

void Container::remove(const Registration& registration) {
    int index = index_of(registration);
    if (index < 0) return;

    if (vehicles[index]->has_owner())
        vehicles[index]->get_owner()->release(vehicles[index]->get_registration());

    delete vehicles[index];
    vehicles.erase(vehicles.begin() + index);
}

void Container::acquire(unsigned id, const Registration& registration) {
    Person* person = find(id);
    if (!person) throw range_error("No such person");

    Vehicle* vehicle = find(registration);
    if (!vehicle) throw range_error("No such vehicle");

    if (vehicle->has_owner()) vehicle->get_owner()->release(vehicle->get_registration());

    person->acquire(vehicle);
}

void Container::release(unsigned id, const Registration& registration) {
    Person* person = find(id);
    if (!person) throw range_error("No such person");

    Vehicle* vehicle = find(registration);
    if (!vehicle) throw range_error("No such vehicle");

    person->release(vehicle->get_registration());
}

void Container::save(fstream& file) const {
    for (const Vehicle* v : vehicles) file << "VEHICLE " << *v;
    for (const Person* p : people) p->save(file);
}

void Container::print_people() const {
    if (people.empty()) {
        cout << "No people\n";
        return;
    }

    for (const Person* p : people) p->print();
}

void Container::print_vehicles() const {
    if (vehicles.empty()) {
        cout << "No vehicles\n";
        return;
    }

    for (const Vehicle* v : vehicles) v->print();
}

void Container::print(unsigned id) const {
    const Person* p = find(id);
    if (p)
        p->print();
    else
        cout << "No person with id " << id << endl;
}

void Container::print(const Registration& registration) const {
    const Vehicle* v = find(registration);
    if (v)
        v->print();
    else
        cout << "No vehicle with registration " << registration << endl;
}
