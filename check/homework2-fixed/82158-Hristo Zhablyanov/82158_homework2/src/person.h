#pragma once

#include <fstream>
#include <vector>

#include "vehicle.h"

using std::fstream;
using std::vector;

class Person {
  private:
    unsigned id;
    string name;
    vector<Vehicle*> vehicles;

  public:
    Person() = delete;
    Person(const Person& other) = delete;

    Person(unsigned _id, string _name);

    unsigned get_id() const;
    bool has_vehicles() const;

    void acquire(Vehicle* vehicle);
    void release(const Registration& registration);
    void clear();

    void save(fstream& file) const;
    void print() const;

    friend ostream& operator<<(ostream& os, const Person& p);
};
