#pragma once
#include <string>

class Registration {

    static const unsigned lengthSeven = 7;
    static const unsigned lengthEight = 8;
    
    bool isValid(std::string licensePlate);
    bool lengthSevenValidation(std::string licensePlate);
    bool lengthEightValidation(std::string licensePlate);

    void copy(const Registration& other);

    std::string licensePlate;
public:
    Registration();
    Registration(std::string licensePlate);
    Registration(const Registration& other);

    Registration& operator=(const Registration& other);
    
    // muatator
    void setLicensePlate(std::string other);
    // accessor
    std::string getLicensePlate(); 

    friend bool operator==(const Registration& lhs, const Registration& rhs);
    friend std::istream& operator>>(std::istream& in, Registration& registration);
    friend std::ostream& operator<<(std::ostream& out, const Registration& registration);
};
