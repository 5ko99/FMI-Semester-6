#ifndef VEHICLE_HH
#define VEHICLE_HH

using namespace std;

#include "Person.h"
#include "Registration.h"




class Vehicle
{
    const Registration* license_plate;
    string info;
    Person* owner;

    void copy (const Registration* _license_plate, const string& _info, Person* _owner);

    public:
    Vehicle () = default;
    ~Vehicle ();

    Vehicle (const Registration* _license_plate, const string& _info, Person* _owner);
    Vehicle (const Registration* _license_plate, const string& _info);
    Vehicle (const Vehicle& other);

    Vehicle& operator = (const Vehicle& other);
    const Registration* getRegistration();
    Vehicle* clone_veh();
    Person* getOwner();

    string getId();
    void setOwner(Person*);
};


#endif
