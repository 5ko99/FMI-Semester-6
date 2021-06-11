#pragma once
#include "Person.h"
#include <fstream>

class Program
{
private:
    bool running = false;
    std::vector<Person> people;
    std::vector<Vehicle> cars;
    std::vector<std::string> options;
    void addOption(std::string str);

public:
    void getInput(const char *arr);
    void addPerson(const char *name, unsigned int id);
    void addVehicle(const char *registration, const char *description);
    void addVehicleOwner(unsigned int id, const char *registration);
    void releaseVehicle(unsigned int id, const char *registration);
    void remove(const char *what);
    void save(const char *path);
    void show(char *option);
    void run();
    void load(const char *path);
    bool isRunning();
    std::vector<std::string> getOptions();
};
