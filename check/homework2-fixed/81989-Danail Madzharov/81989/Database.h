#ifndef DATABASE_HH
#define DATABASE_HH
#include "Vehicle.h"
#include <vector>
#include <set>
using namespace std;

class Database {
    set<unsigned int> peopleIds;
    set<string> vehiclesRegistrations;
    vector<Person*> people;
    vector<Vehicle*> cars;
    bool isPersonFound(Person*);
    bool isCarFound(Vehicle*);

    public:
    vector<Person*> getPeople();
    vector<Vehicle*> getCars();
    void addPerson(Person*);
    void addVehicle(Vehicle*);
    void printAll();
    void setCarOwner(Person*, Vehicle*);
    void removeCarOwner(Person*, Vehicle*);
    bool validateRegNumber(string);
    bool doesPersonExistAlready(unsigned int);
    bool doesVehicleExistAlready(string);  
    void deleteCarFromDatabase(string);
    void deletePersonFromDatabase(unsigned int);
    Person* getPersonById(unsigned int);
    Vehicle* getVehicleByRegNumber(string);
    void printAllPeople();
    void printAllVehicles();
    void printVehicleByRegNumber(string);
    void printPersonById(unsigned int);
    void saveInformationToFile(string);
    set<unsigned int> getpeopleIds();
    set<string> getVehiclesRegistrations();
    ~Database();
};

#endif
