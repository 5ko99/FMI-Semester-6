#ifndef HW_2_COMMANDINTERPETER_H
#define HW_2_COMMANDINTERPETER_H

#include <iostream>
#include "Registration.h"
#include "Vehicle.h"

class CommandInterpreter{
private:
    std::vector<Registration*>* regs;
    std::vector<Vehicle*>* vehicles;
    std::vector<Person*>* people;

    void createVehicle(const std::vector<std::string> & args);
    void createPerson(const std::vector<std::string> & args);
    void acquire(const std::vector<std::string> & args);
    void release(const std::vector<std::string> & args);

    void remove(const std::vector<std::string> & args);

    void save(const std::vector<std::string> & args);

    void show(const std::vector<std::string> & args);

    void showPerson(unsigned id) const;
    void showPeople() const;

    void showVehicle(const std::string& id) const;
    void showVehicles() const;

    void route(std::vector<std::string>& args);

    void purge(Vehicle* wantedVehicle);
    void purge(Person* wantedPerson);

public:

    CommandInterpreter(std::vector<Registration*>& regs, std::vector<Vehicle*>& vehicles, std::vector<Person*>& people);

    void interpret(std::string commandLine);

    static void removeWs(std::string& str);


};

#endif
