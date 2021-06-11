

#ifndef HW2_VEHICLE_H
#define HW2_VEHICLE_H
# include"Registration.h"
# include <string>
class Person;
#ifndef PERSON_H
#define Person_H
# include "Person.h"
#endif

class Vehicle {
private:
    Registration reg;
    std::string descr;
    Person* per;
    bool owned;
    ;
public:
    Vehicle(const Registration&, const std::string&);
    void setOwner(Person*);
    void setRegistration(const Registration&);
    void setDesription(const std::string&);
    void eraseOwner();
    std::string getRegistration()const;
    std::string getDescription()const;
    //Person getOwner()const;
    Person* getOwner()const;
    void print()const;
    bool isItOwned()const;

};
#endif //HW2_VEHICLE_H
