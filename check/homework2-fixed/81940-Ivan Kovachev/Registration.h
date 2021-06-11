#pragma once

#include <iostream>

class Registration
{
    std::string reg;


    bool isDigit(const char &d) const;
    bool isLetter(const char &c) const;

public:
    bool isValid(const std::string reg) const;
    Registration();
    Registration(const std::string reg);
    //Registration(std::string reg);
    Registration(const Registration &other);
    Registration& operator=(const Registration &other);
    std::string getReg();

    friend std::ostream& operator<<(std::ostream&, const Registration& );
    friend bool operator==(const Registration& lhs, const Registration& rhs);

    ~Registration();

};
