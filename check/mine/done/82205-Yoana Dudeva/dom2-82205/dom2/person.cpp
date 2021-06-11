#include "person.h"
#include "vehicle.h"

using std::cout;
using std::endl;
using std::cerr; 
 

void Person::copy(const Person& other)
{
    this->name = other.name;
    this->id = other.id;
    this->vehicles = other.vehicles; 
    
}

Person::Person(const std::string name, const unsigned int id)
{
    this->name = name;
    this->id = id; 
    this->vehicles.clear(); 
}

Person::Person(const std::string name, const unsigned int id, const std::vector<std::string> vehicles)
{
    this->name = name;
    this->id = id; 
    this->vehicles = vehicles; 
}

Person::Person(const Person& other)
{
    copy(other); 
}

void Person::insertVehicle(const Vehicle& add)
{
    for (size_t i = 0; i < this->vehicles.size(); ++i)
    {
        if (vehicles[i] == add.getRegistration().getString())
        {
            cout<<"This vehicle exists!"<<endl;
            return; 
        }
    }

    this->vehicles.push_back(add.getRegistration().getString()); 
}

void Person::eraseVehicle(const Vehicle& erase)
{
    for (size_t i = 0; i < this->vehicles.size(); ++i)
    {
        if (vehicles[i] == erase.getRegistration().getString())
        {
            this->vehicles.erase(this->vehicles.begin()+i);
            cout<<"Vehicle is erased"<<endl;
            return; 
        }
    }
    
    cout<<"This vehicle does not exist!"<<endl;
}

size_t Person::getOwnedVehiclesCount() const
{
    return this->vehicles.size(); 
}

std::string Person::getName() const
{
    return this->name; 
}

unsigned int Person::getId() const
{
    return this->id;
}

std::string Person::getElement(size_t pos)
{
    if (pos >= this->vehicles.size())
    {
        throw std::out_of_range("Invalid index");
    }
   
    return this->vehicles[pos]; 
}

Person& Person::operator=(const Person& person)
{
    if (this != &person)
    {
        copy(person); 
    }

    return *this; 
}


Person::~Person()
{

}
