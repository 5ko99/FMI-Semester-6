#include <iostream>
#include "registration.h"

// checks for valid user input
bool Registration::isValid(std::string licensePlate) {
    
    return (!(licensePlate.length() > lengthEight || licensePlate.length() < lengthSeven)) &&
         ((licensePlate.length() == lengthSeven) ? lengthSevenValidation(licensePlate) : lengthEightValidation(licensePlate));
}

// if the length of the license paltes is seven
bool Registration::lengthSevenValidation(std::string licensePlate) {

    //checks if first symbol is a letter in caps
    if (licensePlate[0] < 'A' || licensePlate[0] > 'Z')
        return false;

    //checks if the next 4 symbols are digits
    for (size_t i = 1; i < 5; ++i) {
        if (licensePlate[i] < '0' || licensePlate[i] > '9')
            return false;
    }
    //checks if last 2 symbols are letters in caps
    for (size_t i = 5; i < 7; ++i) {
        if (licensePlate[i] < 'A' || licensePlate[i] > 'Z')
            return false;
    }
    
    return true;
}

bool Registration::lengthEightValidation(std::string licensePlate) {

    //checks if the first  two symbols are letters in caps
    for (size_t i = 0; i < 2; ++i) {
        if (licensePlate[0] < 'A' || licensePlate[0] > 'Z')
            return false;
    }

    //checks if the next 4 symbols are digits
    for (size_t i = 2; i < 6; ++i) {
        if (licensePlate[i] < '0' || licensePlate[i] > '9')
            return false;
    }

    //checks if last 2 symbols are letters in caps
    for (size_t i = 6; i < 8; ++i) {
        if (licensePlate[i] < 'A' || licensePlate[i] > 'Z')
            return false;
    }

    return true;
}

void Registration::copy(const Registration& other) {

    licensePlate = other.licensePlate;
}

Registration::Registration() {
    
    licensePlate = "N/A";
}

Registration::Registration(std::string licensePlate) {
    // if the input is incorrect, throw excp
    try {
        if(!isValid(licensePlate)) {
            throw std::invalid_argument("Incorrect license plate.\n");
        }
    }
    catch(std::invalid_argument& e) {
        std::cout << e.what();
    }

    this->licensePlate = licensePlate;
}

Registration::Registration(const Registration& other) {

    copy(other);
}

Registration& Registration::operator=(const Registration& other) {

    if (this != &other) {
        copy(other);
    }

    return *this;
}

void Registration::setLicensePlate(std::string other) {

    licensePlate = other;
}

std::string Registration::getLicensePlate() {

    return licensePlate;
}

bool operator==(const Registration& lhs, const Registration& rhs) {

    return lhs.licensePlate == rhs.licensePlate;
}

std::istream& operator>>(std::istream& in, Registration& registration) {

    in >> registration.licensePlate;

    return in;
}

std::ostream& operator<<(std::ostream& out, const Registration& registration) {

    out << registration.licensePlate;

    return out;
}
