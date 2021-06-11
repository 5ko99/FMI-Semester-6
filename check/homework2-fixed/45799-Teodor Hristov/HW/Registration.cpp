#include <string>
#include <iostream>
#include <vector>
#include "Registration.h"

#define MAX_LEN 8
#define MIN_LEN 7

const std::string &Registration::getRegistrationNumber() const {
    return registrationNumber;
}

void Registration::setRegistrationNumber(const std::string &registrationNumber) {
    if(isNumberValid(registrationNumber)){
        Registration::registrationNumber = registrationNumber;
    } else {
        throw std::invalid_argument("Not valid registration number!");
    }
}
Registration::Registration() {
    this->registrationNumber = "";
}
Registration::Registration(const std::string &number) {
    setRegistrationNumber(number);
}

bool Registration::isNumberValid(const std::string &number){
    // 7 <= len <= 8
    std::size_t len = number.length();

    if(len > MAX_LEN || len < MIN_LEN){
        return false;
    }else {
        if(len == 7){
            //C1234AB
            return isalpha(number[0]) && isdigit(number[1]) &&
                    isdigit(number[2]) && isdigit(number[3]) &&
                    isdigit(number[4]) && isalpha(number[0]) && isalpha(number[0]);
        } else {
            //XY1111YX
            return isalpha(number[0]) && isalpha(number[1]) &&
                    isdigit(number[2]) && isdigit(number[3]) &&
                    isdigit(number[4]) && isdigit(number[5]) &&
                    isalpha(number[6]) && isalpha(number[7]);
        }
    }

}

bool Registration::registrationExists(std::string& reg, std::vector<Registration*>* vect){
    Registration registr;
    try {
        registr = Registration(reg); // this is needed only for searching
    } catch(...){
        return false;
    }
    return registrationExists(registr, vect);
}

bool Registration::registrationExists(Registration& reg, std::vector<Registration*>* vect){
    for (int i = 0; i < vect->size(); i++) {
        if(*(*vect)[i] == reg) {
            return true;
        }
    }
    return false;
}

bool Registration::operator==(const Registration &rhs) const {
    return registrationNumber == rhs.registrationNumber;
}

bool Registration::operator!=(const Registration &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &out, const Registration &reg) {
    if(&reg == nullptr){
        throw std::invalid_argument("Registration must be valid object!");
    }

    out << reg.registrationNumber << std::endl;
    return out;
}
