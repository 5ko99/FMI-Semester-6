#pragma once
#include <string>
#include <iostream>
class Registration {
private:
    std::string registration = "";
public:
    Registration();
    Registration(const std::string& other);
    Registration(const Registration& other);
    Registration& operator=(const Registration& other);
    bool operator== (const Registration& other);
    ~Registration();
    void print() const;
    std::string getRegistration() const;

};
