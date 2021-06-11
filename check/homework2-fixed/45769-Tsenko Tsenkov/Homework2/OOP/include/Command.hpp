#pragma once

#include "../include/Executor.hpp"

#include <string>
#include <sstream>

class Command
{
public:
    Command(const std::string name, Executor &executor) : name{name}, executor{executor} {}

    std::string get_name() const { return name; }
    Executor &getExecutor() { return executor; }

    virtual void execute(std::istringstream &arguments) = 0;

private:
    std::string name;
    Executor &executor;
};
