#pragma once
#ifndef __Vehicle__HH
#define __Vehicle__HH

#include "Registration.h"

class Person;

class Vehicle
{
    private:
    Registration unique_reg;
    std::string details;
    unsigned int owner;


    void copy(const Vehicle& other);
    void clean();


    public:
    Vehicle();
    Vehicle(const Vehicle& other);
    Vehicle& operator=(const Vehicle& other);
    ~Vehicle();
    Vehicle(const Registration _unique_reg, const std::string _details);
    Vehicle(const Registration _unique_reg, const std::string _details, unsigned owner);
    Registration getReg() const;
    std::string getDetails() const;
    unsigned int getOwner() const;
    bool isThereAnOwner() const; 
    void insertOwner(const Person& person); 
    void eraseOwner(); 

};

#endif
