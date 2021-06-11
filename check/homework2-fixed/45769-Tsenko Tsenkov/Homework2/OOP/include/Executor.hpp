#pragma once

#include <vector>
#include <iostream>
#include <list>
#include <string>

#include "../include/Vehicle.hpp"

class Command;

class Executor
{
public:
    void run(std::istream &in, std::ostream &out);
    void add_command(Command *com);

    std::list<Person *> people;
    std::list<Vehicle *> vehicles;

    static std::string str_tolower(std::string s);
    Command *get_command(const std::string &name) const;
private:
    std::vector<Command *> commands;
};
