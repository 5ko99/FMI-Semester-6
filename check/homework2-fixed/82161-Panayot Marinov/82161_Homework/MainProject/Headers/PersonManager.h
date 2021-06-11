#pragma once
#ifndef PERSONMANAGER_H
#define PERSONMANAGER_H

#include "Person.h"
#include<iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

//class Person;

class PersonManager {
    vector<Person*> people;
    
    public:      
        void addPerson(const string& name);
        void removePerson(size_t id);
        void removePerson(const string& id);
        Person* findPerson(size_t id);
        Person* findPerson (const string& id);
        size_t getNumberOfPeople() const;
        void showAllPeople(std::ostream& out);
        void showAllPeopleDetailed(std::ostream& out);
        Person& at(size_t pos);
	    const Person& at(size_t pos) const;
        Person& operator[](size_t pos);
        const Person& operator[](size_t pos) const;
};

#endif //PERSONMANAGER_H
