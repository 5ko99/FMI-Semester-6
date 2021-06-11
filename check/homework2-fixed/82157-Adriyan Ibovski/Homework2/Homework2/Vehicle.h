#pragma once
#include "Registration.h"
#include <vector>
class Person;

class Vehicle{
private:
    Registration m_reg;
    string m_desc;
    Person* m_owner;
public:
    Vehicle(const Registration& reg, const string& desc, Person* owner = nullptr);
    ~Vehicle() = default;
    Vehicle(const Vehicle& other) = default;
    Vehicle(Vehicle&& other) noexcept;
    Vehicle& operator=(const Vehicle& other);
    Vehicle& operator=(Vehicle&& other) noexcept;

    Registration getReg() const;
    string getDesc() const;
    void setOwner(Person* owner);
    Person* getOwner() const;
};
