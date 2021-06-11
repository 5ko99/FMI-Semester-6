#include "Vehicle.h"

using namespace std;


void Vehicle::copy (const Registration* _license_plate, const string& _info, Person* _owner)
{
    license_plate = _license_plate;
    info = _info;
    owner = _owner;
}

Vehicle::Vehicle ( const Registration* _license_plate, const string& _info, Person* _owner)
{
    copy(_license_plate, _info, _owner);
}

Vehicle::Vehicle (const Registration* _license_plate, const string& _info)
{
    license_plate = _license_plate;
    info = _info;
}

Vehicle::Vehicle (const Vehicle& other)
{
    copy (other.license_plate, other.info, other.owner);
}

Vehicle* Vehicle::clone_veh ()
{
    return new Vehicle(*this);
}

Vehicle& Vehicle::operator = (const Vehicle& other) {
    if (this != &other) 
    {
        copy(other.license_plate, other.info, other.owner);
    }
    return *this;
}

Vehicle:: ~Vehicle () {
    if ( !owner ) {
        delete owner;
    }
        cout<<"destroyed owner\n";
    }

string Vehicle::getId() 
{
    return license_plate->getRegNum();
}

void Vehicle::setOwner(Person* newOwner) 
{
    owner = newOwner;
}

const Registration* Vehicle::getRegistration() {
    return this->license_plate;
}

Person* Vehicle::getOwner() {
    return this->owner;
}
