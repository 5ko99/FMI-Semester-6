#pragma once

#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <string>

class Registration
{
    const int MAX_LENGTH = 8;
    const int MIN_LENGTH = 7;
    int m_length = 0;
    std::string m_reg = "";

public:
    Registration() = default;
    Registration(const std::string& reg);

    Registration& operator=(const Registration& reg);

    const std::string& getReg() const;

    void calculateLength();
    bool isValidReg();
    bool operator==(const Registration& reg);

    friend std::ostream& operator<<(std::ostream& out, const Registration& reg);
};

#endif
