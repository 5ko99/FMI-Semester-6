#pragma once

#include "registration.h"

using std::cin;
using std::cout;
using std::endl;

class Person;
ostream& operator<<(ostream& os, const Person& p);

class Vehicle {
  private:
    friend Person;

    Registration registration;
    string description;
    Person* owner = nullptr;

  public:
    Vehicle() = delete;
    Vehicle(const Vehicle& other) = delete;

    Vehicle(const Registration& _registration, string _description);

    const Registration& get_registration() const;
    bool has_owner() const;
    Person* get_owner() const;

    void print() const;

    friend ostream& operator<<(ostream& os, const Vehicle& v);
};
