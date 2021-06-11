#pragma once
#include <vector>
#include "header.h"
class Solution
{
    std::vector<Vehicle> vehicles;
    std::vector<Person> people;
    std::string stringInQuotes(std::istream &in);

public:
    Solution();
    void vehicle(Registration &reg, std::string &desc);
    void person(std::string &name, unsigned int id);
    void acquire(unsigned int id, Registration &reg);
    void release(unsigned int id, Registration &reg);
    void remove(std::string &what);
    void save(std::string &path);
    void show(std::string &option);
    void execCommand(std::istream &in);
    friend class SolutionTest;
};
class SolutionTest
{
public:
    Solution sol;

    Person &personAt(int pos)
    {
        return sol.people[pos];
    }
    Vehicle &vehiclesAt(int pos)
    {
        return sol.vehicles[pos];
    }
    int cntPeople()
    {
        return sol.people.size();
    }
    int cntVehicles()
    {
        return sol.vehicles.size();
    }
};
