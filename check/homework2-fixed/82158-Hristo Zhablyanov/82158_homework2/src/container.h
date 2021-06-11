#pragma once

#include <new>

#include "person.h"

using std::nothrow;
using std::range_error;

class Container {
  private:
    vector<Person*> people;
    vector<Vehicle*> vehicles;

    int index_of(unsigned id) const;
    int index_of(const Registration& registration) const;

    Person* find(unsigned id) const;
    Vehicle* find(const Registration& registration) const;

  public:
    Container(const Container& other) = delete;

    Container() = default;
    ~Container();

    bool contains(unsigned id) const;
    bool contains(const Registration& registration) const;

    bool is_dependant(unsigned id) const;
    bool is_dependant(const Registration& registration) const;

    void push(unsigned int id, string name);
    void push(const Registration& registration, const string& description);

    void remove(unsigned id);
    void remove(const Registration& registration);

    void acquire(unsigned id, const Registration& registration);
    void release(unsigned id, const Registration& registration);

    void save(fstream& file) const;
    void print_people() const;
    void print_vehicles() const;
    void print(unsigned id) const;
    void print(const Registration& registration) const;
};
