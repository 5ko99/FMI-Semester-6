#ifndef PERSONMANAGER_H
#define PERSONMANAGER_H

#include<iostream>
#include<exception>
#include<string>
#include<vector>
#include"main.h"

class PersonManager{
    private:
        std::vector<Person*> people;
    public:
        PersonManager();
        ~PersonManager();
        bool AddPerson(Person* personToAdd);
        bool RemovePerson(unsigned int personId);
        Person* GetPersonById(unsigned int personId);
        std::vector<Person*> GetAll();
};

#endif
