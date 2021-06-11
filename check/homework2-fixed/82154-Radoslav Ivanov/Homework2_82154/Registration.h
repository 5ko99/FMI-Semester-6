#pragma once
#include <string>

class Registration {

private:
    std::string registration;

public:
    Registration();
    Registration (const std::string& reg);
    Registration (const Registration& other);
    Registration& operator=(const Registration& other);
    ~Registration() = default;
    bool operator==(const Registration& other) const;
    
    friend std::ostream& operator<<(std::ostream &os, const Registration& reg);

    static bool validateRegistration(const std::string& newReg);
};
