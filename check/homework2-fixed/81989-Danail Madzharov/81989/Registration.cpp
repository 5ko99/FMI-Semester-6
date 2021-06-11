#include "Registration.h"
#include <regex>
#include <iostream>
using namespace std;


Registration::Registration(string newRegNumber) {
    if(validateReg(newRegNumber)){
        this->regNumber = newRegNumber;
    } else {
        cout<<"Number is invalid";
        return;
    }
}

string Registration::getRegNumber() {
    return this->regNumber;
}

bool Registration::validateReg(std::string registrationNumber) {
    regex r("[A-Z][A-Z][0-9][0-9][0-9][0-9][A-Z][A-Z]");
    regex r2("[A-Z][0-9][0-9][0-9][0-9][A-Z][A-Z]");
    return regex_match(registrationNumber, r) | regex_match(registrationNumber, r2);
}
