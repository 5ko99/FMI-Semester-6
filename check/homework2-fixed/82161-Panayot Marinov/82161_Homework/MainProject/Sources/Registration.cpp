#include"../Headers/Registration.h"
#include"../Headers/ValidationUtils.h"
#include"../Headers/Constants.h"
#include <stdexcept>
#include <cstring>
#include <cstddef>
#include <string>

using std::string;

Registration::Registration(const char* registrationString) {
    if(!ValidationUtils::isValidNumberPlate(registrationString))
        throw std::invalid_argument("Incorrect numberPlate format");

    copyNumberPlate(this->registrationString, registrationString);
    this->length = strlen(registrationString);
}

Registration::Registration(const string& registrationString) {
    if(!ValidationUtils::isValidNumberPlate(registrationString.c_str()))
        throw std::invalid_argument("Incorrect numberPlate format");

    copyNumberPlate(this->registrationString, registrationString.c_str());
    this->length = registrationString.length();
}

Registration::Registration(const Registration& rhs) {
    copyNumberPlate(this->registrationString, rhs.registrationString);
    this->length = rhs.length;
}

Registration& Registration::operator=(const Registration& rhs) {
    if(this != &rhs) {
        copyNumberPlate(this->registrationString, rhs.registrationString);
        this->length = rhs.length;
    }

    return *this;
}

void Registration::copyNumberPlate(char* arr1, const char* arr2) {
    unsigned i = 0;
    while(arr2[i] != '\0') {
        arr1[i] = arr2[i];
        i++;
    }
    arr1[i] = '\0';
}

const char* Registration::c_str() const {
    return registrationString;
}

bool Registration::operator==(const Registration& rhs) const {
    return 
        (strcmp(registrationString, rhs.registrationString) == 0) &
        (length == rhs.length);
}

std::ostream& operator<<(std::ostream& out, const Registration& r) {
    out<<r.c_str();
    
    return out;
}
