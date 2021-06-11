#include "People.h"
#include <iostream>

People::~People ()
{
    for (size_t i=0; i<people.size(); ++i){
        delete people[i];
    }
    people.clear();
}

//Validation of pos is not necessary for the use of the method in this program
Person* People::operator[](unsigned pos)
{
    return people[pos];
}

Person*& People::getPerson (unsigned id) 
{
    for (size_t i=0; i<people.size(); ++i){
        if (people[i]->getId() == id){
            return people[i];
        }
    }
    throw std::invalid_argument("Person not found!");
}

size_t People::getCount() const
{
    return people.size();
}

void People::addPerson(Person& newPerson)
{
    try {
        Person* found = getPerson(newPerson.getId());  
        //if getPerson() throws, it means there is no such person
        //In the current situation this is what we are looking for 
    } catch (std::invalid_argument& e){
        Person* newPer = new Person(newPerson);
        people.push_back(newPer);
        return;
    }
    throw std::invalid_argument("There is already a person with this ID!");
}

void People::removePerson(unsigned id)
{
    Person** found = &getPerson(id); //cannot throw because of the implementation of the command REMOVE
    (**found).releaseAllVehicles(); 
    delete (*found);
    std::swap(*found, people.back());
    people.pop_back();
    //Using double pointer, std::swap and pop_back() instead of making an additional
    //method which finds the index in the vector of person* and using erase() 
}

void People::addVehicleToPerson (Vehicle& newVehicle, unsigned id)
{
    getPerson(id)->addVehicle(newVehicle);
}


void People::releaseVehicleFromPerson (const Registration& reg, unsigned id)
{
    getPerson(id)->releaseVehicle(reg);
}


void People::showInfo(unsigned id)
{
    getPerson(id)->printInfo();
}

void People::showAllInfo() const
{
    size_t i=0;
    std::cout << "\n";
    for (i; i<people.size(); ++i){
        people[i]->printInfo();
        std::cout << "\n";
    }
    if (i == 0){
        std::cout << "No people registered yet!\n" << std::endl;
    }
}
