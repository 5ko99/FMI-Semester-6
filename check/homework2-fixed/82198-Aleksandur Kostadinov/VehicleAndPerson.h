#include <vector>
#include <string>
#include "Registration.h"

#pragma once

class Vehicle;

class Person
{
private:
    unsigned int person_id;
    std::string name;
    std::vector<Vehicle> vehicles;

public:
    Person();
    Person(std::string name, unsigned int id);
    bool operator==(const Person &other);
    Person(const Person &other);
    Person &operator=(const Person &other);
    void clear();
    void add_vehicle(Vehicle &vehicle);

    std::string get_name() const { return this->name; }
    friend std::vector<Vehicle> &get_all_vehicles(Person *person) { return person->vehicles; }
    unsigned int get_id() const { return this->person_id; }

    bool in_vehicles(const Vehicle &other) const;

    static std::vector<Person> existing_people;
    static size_t count_of_existing_people;
    static void print_person(unsigned int id);
    static bool in_existing_people(const Person &other);
    static void print_vehicles(const Person &person);
    static void print_all_people();
    static void remove_person(unsigned int id);

private:
    void copy(const Person &other);
    static void swap(size_t i, size_t j, std::vector<Person> &people);
};

class Vehicle
{
private:
    Registration vehicle_id;
    std::string description;
    Person *owner;

public:
    Vehicle();
    Vehicle(std::string desc, const Registration &other);
    Vehicle(const Vehicle &other);
    Vehicle &operator=(const Vehicle &other);
    void add_owner(Person &person);

    void release_owner();

    bool is_free() const;
    bool operator==(const Vehicle &other) const;
    void clear();
    void set_owner(Person *person);
    std::string get_desc() const { return this->description; }
    Person *get_owner() { return this->owner; }
    Registration get_id() const { return this->vehicle_id; }

    static std::vector<Vehicle> existing_vehicles;
    static size_t count_of_existing_vehicles;
    static void print_vehicle(const Registration &id);
    static bool in_existing_vehicles(const Vehicle &v);
    static void print_all_vehicles();
    static void remove_vehicle(const Registration &other);

private:
    void copy(const Vehicle &other);
    static void swap(size_t i, size_t j, std::vector<Vehicle> &vehicles);
};
