#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstring>
#include <vector>

#include "..\Headers\Registration.hpp"
#include "..\Headers\Vehicle.hpp"

class Person {
   private:
    std::string namePerson;
    unsigned int identifierPerson;
    std::vector<Vehicle *> ownedVehicles;

    static std::vector<unsigned int> identifiers;

   public:
    //! Person constructor
    Person(std::string namePersonInput, unsigned int identifierPersonInput);

    std::string getName();
    unsigned int getIdentifier();
    std::vector<Vehicle *> getOwnedVehicles();

    void acquireVehicleToPerson(Vehicle *vehicle);
    void releaseVehicle(const char regNumberInput[9]);
    void emptyVehicle();

    //! Person destructor
    ~Person();
};

#endif
