#ifndef __REGISTRATION_HH__
#define __REGISTRATION_HH__

#include<iostream>
#include<cstring>
#include<vector>
#include<exception>

//the class for the registration number of the vehicles
class Registration {
    char registrationNumber[9]; //1 or 2 letters for the town/city, 4 digits and 2 more letters
    
    bool isValidLetter(char current); //checks if the current char is a capital letter
    bool isDigit(char current);//checks if the current char is a digit
    bool isValidRegNumber(const char* otherRegistration);//validates the registration number
    
    public:
    Registration(const char* otherRegistration); //a constructor for the registration number
    
    const char* getRegNumber() const; //a selector for the registration number
    bool operator ==(const Registration& otherRegistration) const; //returns if two registration numbers are identical
};

#endif
