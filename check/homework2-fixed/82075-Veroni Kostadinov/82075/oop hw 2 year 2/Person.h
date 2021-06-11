#ifndef PERSON_HH
#define PERSON_HH

using namespace std;
#include "Vehicle.h"

#include <iostream>

#include <vector>



class Person
{
    string name;
    unsigned int person_id;
    vector<Vehicle*> person_vehicles;

    void copy(const string& _name, const unsigned int& _person_id, vector<Vehicle*> _person_vehicles);
    void destruct();


    public:
    Person () = default;
 
    //Person (const string& _name, const unsigned int& _person_id, vector<Vehicle*> _person_vehicles);
    //Person (const Person& other);
    Person(const string _name, const unsigned int _person_id);
    ~Person ();

    unsigned int getId();

    vector<Vehicle*> getOwnedVehicles();

    void addVehicle(Vehicle*);
    Person* clone_person();



};

#endif
