#ifndef DOMASHNA_2_OOP_2021_REGISTRATION_H
#define DOMASHNA_2_OOP_2021_REGISTRATION_H
#include <iostream>
//#include "Person.h"
//#include "Vehicle.h"
class Registration {
private:
    std::string reg;
public:
//    Registration();
    Registration(const std::string& reg);
    Registration(const Registration& other);
    Registration& operator=(const Registration& other);
    ~Registration();
    const std::string& get_registration()const;
    bool operator==(const Registration& reg)const;

    friend void swap(Registration& first,Registration& second);
};


#endif //DOMASHNA_2_OOP_2021_REGISTRATION_H
