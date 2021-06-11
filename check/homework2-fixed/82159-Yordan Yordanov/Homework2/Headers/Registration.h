#pragma once

#include <iostream>
#include <string>

class Registration {
private:
    std::string registration;

public:
    Registration() = default;

    Registration(const std::string &registration);

    Registration(const Registration &object);

    ~Registration() = default;

public:
    const std::string &getRegistration() const;

public:
    Registration &operator=(const Registration &object);

    friend std::ostream &operator<<(std::ostream &os, const Registration &object);
};
