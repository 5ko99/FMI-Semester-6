#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Registration.hpp"
#include "Person.hpp"
#include "Vehicle.hpp"
#include <fstream>

class Controller
{
    friend class Vehicle;

    std::vector<Person*> people;
    std::vector<Vehicle*> vehicles;

    Person* find(unsigned int id);

    Vehicle* find(const Registration& reg);

    std::vector<Person*>::iterator findIterator(unsigned int id);

    std::vector<Vehicle*>::iterator findIterator(const Registration& reg);

    Person* findPersonByVehicle(Registration& reg);

 public:

    Controller() = default;

    ~Controller();

    static Controller& getInstance();

    Controller(Controller const&) = delete;

    void operator=(Controller const&) = delete;

    Vehicle& create(const Registration& reg, const std::string& desc);

    Person& create(const std::string& name, unsigned int id);

    void acquire(unsigned int id, const Registration& reg);

    void release(unsigned int id, const Registration& reg);

    bool remove(unsigned int id, bool interactive = false);

    void remove(const Registration& reg, bool interactive = false);

    void show(std::string s);

    void show(unsigned int id);

    bool save(const std::string& path);

    void load(const std::string& path);

    void run(std::istream& src, bool interactive = false);
};

#endif
