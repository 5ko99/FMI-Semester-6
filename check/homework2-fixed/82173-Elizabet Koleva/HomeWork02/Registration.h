#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;

// Max available symbols
const size_t CAR_PLATE_SYMBOLS = 8;

class Registration {

private:
    string regNumber;
   
    void capitaliseLetters(); // Letters of the registration
    
    bool checkRegNumb() const; // checking if the reg is in the correct format

public:
    //Registration();

    Registration(const string& newRegNumb);

    Registration(const Registration& newRegistr);

    string getRegNumber() const;

    Registration operator=(const Registration& other); //assigning one to another reg

    bool operator==(const Registration& other) const; //if the registrations are the same

};



#endif
