#include "vehicle.h"
#include "person.h"

using std::cout;
using std::endl;
using std::cerr; 

void Vehicle::copy(const Vehicle& other)
{
    this->uniqueRegistration = other.uniqueRegistration;
    this->description = other.description;
    this->ownerID = other.ownerID; 
}


Vehicle::Vehicle(const Registration reg, const std::string descr)
{
    this->uniqueRegistration = reg; 
    this->description = descr; 
    this->ownerID = -1; 

}

Vehicle::Vehicle(const Registration reg, const std::string descr, unsigned ownerID)
{
    this->uniqueRegistration = reg;
    this->description = descr;
    this->ownerID = ownerID; 
}

Vehicle::Vehicle(const Vehicle& other)
{
    copy(other);
}


Registration Vehicle::getRegistration() const
{
    return this->uniqueRegistration; 
}

std::string Vehicle::getDescription() const
{
    return this->description; 
}

int Vehicle::getOwnerID() const
{
    return this->ownerID;
}

bool Vehicle::isThereAnOwner() const
{
    return this->ownerID >= 0; 
}


void Vehicle::insertOwner(const Person& person)
{
    if (this->ownerID >= 0)
    {
        cout<<"There is already an owner!"<<endl;
        return; 
    }

    this->ownerID = person.getId();
    cout<<"Owner added!"<<endl;

}

void Vehicle::eraseOwner()
{
    this->ownerID = -1;
    cout<<"Owner erased!"<<endl;
}


Vehicle& Vehicle::operator=(const Vehicle& vehicle)
{
    if (this != &vehicle)
    {
        copy(vehicle);
    }

    return *this; 
} 

Vehicle::~Vehicle()
{
    
}
