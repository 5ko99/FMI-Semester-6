//#define _CRT_SECURE_NO_WARNINGS
#include "Data.h"
#include <vector>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include "helpers.h"
#include <fstream>

Data::Data(){}
//----------------------Method to create an instance----------------------
Data& Data::getInstance()
{
    static Data d;
    return d;
}
//--------------------------Database operations---------------------------
Person* Data::newPerson(const char* name, unsigned int id)
{
    Person* toBeAdded=findPerson(id);
    if(toBeAdded) {throw std::invalid_argument("Cannot have people with identical ids.");}
    toBeAdded=new Person(name, id);
    people.push_back(toBeAdded);
    return toBeAdded;
}
Vehicle* Data::newVehicle(const char* registration, const char* description)
{
    Vehicle* toBeAdded=findVehicle(registration);
    if(toBeAdded) {throw std::invalid_argument("Cannot have vehicles with identical registrations.");}
    toBeAdded=new Vehicle(registration, description);
    vehicles.push_back(toBeAdded);
    return toBeAdded;
}
Person* Data::findPerson(unsigned int id) const
{
    std::size_t nump = numberOfPeople();
    for(std::size_t i = 0; i<nump; ++i)
        if(people[i]->getId() == id) return people[i];
    return nullptr;
}
Vehicle* Data::findVehicle(const char* registration) const
{
    std::size_t numv = numberOfVehicles();
    for(std::size_t i = 0; i<numv; ++i)
        if(std::strcmp(vehicles[i]->getRegistration(), registration) == 0)
            return vehicles[i];
    return nullptr;
}
void Data::removePerson(unsigned int id)
{
    std::size_t nump=numberOfPeople();
    std::size_t i=0;
    for(i; i<nump; ++i)
    {
        if(people[i]->getId()==id)
        {
            if(people[i]->numberOfVehiclesOwned()!=0)
            {
                std::cout<<"This person owns vehicles. Please confirm removal with y/n: ";
                if(readAbinaryAnwser()=='n') return;
                people[i]->releaseAll();
            }
            delete people[i];
            people.erase(people.begin()+i);
            std::cout<<"Successfully removed person."<<std::endl;
            return;
        }
    }
    if(i==nump) throw std::invalid_argument("No such person exists.");
}
void Data::removeVehicle(const char* registration)
{
    std::size_t numv=numberOfVehicles();
    std::size_t i=0;
    for(i=0; i<numv; ++i)
    {
        if(std::strcmp(vehicles[i]->getRegistration(), registration)==0)
        {
            if(vehicles[i]->owned())
            {
                std::cout<<"This vehicle has an owner. Please, confirm removal with y/n: ";
                if(readAbinaryAnwser()=='n') return;
                vehicles[i]->removeOwner();
            }
            delete vehicles[i];
            vehicles.erase(vehicles.begin()+i);
            std::cout<<"Successfully removed vehicle."<<std::endl;
            return;
        }
    }
    if(i==numv) throw std::invalid_argument("No such vehicle exists.");
}
void Data::remove(const char* what)
{
    if (isStringRegistration(what)) removeVehicle(what);
    else if(isStringId(what)) removePerson(strToUnsigned(what));
    else throw std::invalid_argument("Incorrect argument.");
}

void Data::acquire(const char* who, const char* what)
{
    if (!isStringId(who) || !isStringRegistration(what)) { throw std::invalid_argument("Incorrect arguments."); }
    Person* p = findPerson(strToUnsigned(who));
    Vehicle* v = findVehicle(what);
    if (!p) { throw std::invalid_argument("No such person exists."); }
    if (!v) { throw std::invalid_argument("No such vehicle exists.");}
    p->acquire(v);
}

void Data::release(const char* who, const char* what)
{
    if (!isStringId(who) || !isStringRegistration(what))
        { throw std::invalid_argument("Incorrect arguments."); }
    Person*  p = findPerson(strToUnsigned(who));
    Vehicle* v = findVehicle(what);
    if (!p) { throw std::invalid_argument("No such person exists.");  }
    if (!v) { throw std::invalid_argument("No such vehicle exists.");}
    p->release(v);
}
std::size_t Data::numberOfVehicles() const {return vehicles.size();}
std::size_t Data::numberOfPeople()   const {return people.size();  }

//----------------------------Show methods--------------------------------
void Data::showVehicles() const
{
    std::size_t numv = numberOfVehicles();
    std::cout << "Vehicles existing: " << '\n';
    for (std::size_t i = 0; i < numv; ++i)
        std::cout << vehicles[i]->getRegistration() << '\n';
}
void Data::showPeople() const
{
    std::size_t nump = numberOfPeople();
    std::cout << "People existing: " << '\n';
    for (std::size_t i = 0; i < nump; ++i)
    std::cout << people[i]->getId() << '\n';
}
void Data::showVehicle(const char* registration) const
{
    Vehicle* v = findVehicle(registration);
    if (!v)
        { throw std::invalid_argument("No such vehicle exists."); }
    std::cout << (*v);
}
void Data::showPerson(unsigned int id) const
{
    Person* p = findPerson(id);
    if(!p)
        { throw std::invalid_argument("No such person exists."); }
    std::cout << (*p);
}
void Data::show(const char* what) const
{
    if (isStringRegistration(what))
        showVehicle(what);
    else if (isStringId(what))
        showPerson(strToUnsigned(what));
    else if (caseInsensitiveCmp(what, "PEOPLE") == 0)
        showPeople();
    else if (caseInsensitiveCmp(what, "VEHICLES") == 0)
        showVehicles();
    else throw std::invalid_argument("Incorrect argument.");
}

//-------------------------File/Stream operations-------------------------
void Data::save(std::ofstream& oFile) const
{
    std::size_t numv=numberOfVehicles();
    std::size_t nump=numberOfPeople();
    for(std::size_t i=0; i<nump; ++i)
    {
        oFile<<"PERSON ";
        const char* name=people[i]->getName();
        if(containsIntervals(name))
            oFile<<'\"'<<name<<'\"';
        else oFile<<name;
        oFile<<' '<<people[i]->getId()<<std::endl;
    }
    for(std::size_t i=0; i<numv; ++i)
    {
        oFile<<"VEHICLE "<<vehicles[i]->getRegistration()<<' ';
        const char* description=vehicles[i]->getDescription();
        if(containsIntervals(description))
            oFile<<'\"'<<description<<'\"'<<'\n';
        else oFile<<description<<'\n';
        if(vehicles[i]->owned())
        {
            oFile<<"ACQUIRE "<<vehicles[i]->getOwnerId()<<" "
            <<vehicles[i]->getRegistration()<<'\n';
        }
    }
}
//-------------------------------Destructor-------------------------------
Data::~Data()
{
    std::size_t numv=numberOfVehicles();
    std::size_t nump=numberOfPeople();
    for(std::size_t i=0; i<nump; ++i) delete people[i];
    for(std::size_t i=0; i<numv; ++i) delete vehicles[i];
}

//------Static member functions for determining the type of a string------
bool Data::isStringId(const char* str)
{
    try { unsigned int id = strToUnsigned(str); }
    catch (...) { return false; }
    return true;
}
bool Data::isStringRegistration(const char* str)
{
    return Registration::isValid(str);
}

