#pragma once
#include "Vehicle.h"
#include "Person.h"
#include <fstream>

using std::vector;

class Command{
private:
    static Command* instance;
    vector<Person> m_person;
    vector<Vehicle> m_vehicle;

    void addVehicle(const Registration& reg, const string& desc);
    void addPerson(const string& name, unsigned int ID);
    void setVehicleOwner(unsigned int ID, const Registration& reg);
    void releaseVehicleOwner(unsigned int ID, const Registration& reg);
    void save(const string& path);
    bool remove(unsigned int ID);
    bool remove(const Registration& reg);

    void showPeople();
    void showVehicles();
    void showVehicle(const string& reg);
    void showPersonbyID(unsigned int ID);
    Vehicle* findVehicle(const Registration& reg);
    Person* findPerson(unsigned  int ID);

    bool findCommand(string t);
    Command() = default;
    ~Command();
public:

    static Command* getInstance();
    void execute(string operation);
    void readLine(const string& line);

};
