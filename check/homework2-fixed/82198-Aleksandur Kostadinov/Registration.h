#include <iostream>
#include "Validation.h"
#pragma once

class Registration
{
private:
    std::string registration;

public:
    Registration(std::string);
    Registration(const Registration &other);
    Registration &operator=(const Registration &other);
    Registration &operator=(const std::string other);
    bool operator==(const Registration &other) const;
    std::string get_registration() const { return this->registration; }
    void clear();

private:
    bool is_valid(std::string) const;
};
