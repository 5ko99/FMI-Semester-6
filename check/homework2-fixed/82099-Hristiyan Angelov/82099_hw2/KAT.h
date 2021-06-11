#ifndef KAT_h
#define KAT_h

#include <stdio.h>
#include "Vehicle.h"
#include "Person.h"

class KAT {
    std::vector<Person*> persons;
    std::vector<Vehicle*> vehicles;

    bool _checkIfVehicleIdIsUnique(RegistrationNumber);
    bool _checkIfIdIsUnique(size_t);

    Result<Vehicle*> _getVehicle(std::string);
    Result<Person*> _getPerson(size_t);

public:
    KAT();
    void registerVehicle(std::string, std::string);
    void registerPerson(std::string, size_t);
    void aquireByVehicleId(size_t, std::string);
    void releaseByVehicleId(size_t, std::string);
    void remove(std::string);
    void removePerson(size_t);
    void removeVehicle(std::string);
    void showVehicles();
    void showPersons();
    void showPersonById(size_t);
    void showVehicleById(std::string);
};

#endif /* KAT_h */
