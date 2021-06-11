#include "Person.h"
using namespace std;

void Person::copy (const string& _name, const unsigned int& _person_id, vector<Vehicle*> _person_vehicles)
{
    name = _name;
    person_id = _person_id;

    for( int i = 0; i < _person_vehicles.size(); i++)
    {
        person_vehicles.push_back(_person_vehicles[i]->clone_veh());
    }

}

// Person::Person ( const string& _name, const unsigned int& _person_id, vector<Vehicle*> _person_vehicles)
// {
//     copy(_name, _person_id, _person_vehicles);
// }

// Person::Person (const Person& other)
// {
//     copy (other.name, other.person_id, other.person_vehicles);
// }

Person::Person(const string _name, const unsigned int _person_id) 
{
    name = _name;
    person_id = _person_id;
}







void Person::destruct ()
{
    for (auto veh : person_vehicles)
    {
        delete veh;
    }
    person_vehicles.clear();
    cout<<"destroyed\n";
}

Person::~Person ()
{
    destruct();
}

unsigned int Person::getId() 
{
    return person_id;
}

void Person::addVehicle (Vehicle* newVehicle) 
{
    person_vehicles.push_back(newVehicle);
}

Person* Person::clone_person ()
{
    return new Person(*this);
}

vector<Vehicle*> Person::getOwnedVehicles() {
    return this->person_vehicles;
}
