#pragma once
#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <iostream>
#include <string>
#include <cstddef>

using std::string;

class Registration {
    char registrationString[9];
    size_t length;


    public:
        const char* c_str() const;
        bool operator==(const Registration& rhs) const;
        Registration(const char* registrationString);
        Registration(const string& registrationString);
        Registration (const Registration& rhs);
        Registration& operator=(const Registration& rhs);
        
        friend std::ostream& operator<<(std::ostream& out, const Registration& r);
    private:
        void copyNumberPlate(char* arr1, const char* arr2);
};

#endif /* REGISTRATION_H */
