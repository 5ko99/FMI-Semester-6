#include "Registration.h"
Registration::Registration() {}
Registration::Registration(const std::string& other){
    if (other.size() == 7){
        if ((other[0] >= 'A' && other[0] <= 'Z')&&
        (other[1] >= '0' && other[1] <= '9') &&
        (other[2] >= '0' && other[2] <= '9') &&
        (other[3] >= '0' && other[3] <= '9') &&
        (other[4] >= '0' && other[4] <= '9') &&
        (other[5] >= 'A' && other[5] <= 'Z')&&
        (other[6] >= 'A' && other[6] <= 'Z')){
            registration = other;
        } else {
            throw std::invalid_argument("wrong registration");
        }
    } else if (other.size() == 8){
        if ((other[0] >= 'A' && other[0] <= 'Z')&&
            (other[1] >= 'A' && other[1] <= 'Z')&&
            (other[2] >= '0' && other[2] <= '9') &&
            (other[3] >= '0' && other[3] <= '9') &&
            (other[4] >= '0' && other[4] <= '9') &&
            (other[5] >= '0' && other[5] <= '9') &&
            (other[6] >= 'A' && other[6] <= 'Z')&&
            (other[7] >= 'A' && other[7] <= 'Z')){
            registration = other;
        } else {
            throw std::invalid_argument("wrong registration");
        }
    } else {
        throw std::invalid_argument("wrong registration");
    }
}
Registration::Registration(const Registration &other):registration(other.registration) {}

Registration &Registration::operator=(const Registration &other) {
    if (this != &other){
        registration = other.registration;
    }
    return *this;
}
Registration::~Registration() {}

void Registration::print() const{
    std::cout << registration;
}

std::string Registration::getRegistration() const{
    return registration;
}

bool Registration::operator==(const Registration &other) {
    if (registration == other.registration){
        return true;
    }
    return false;
}





