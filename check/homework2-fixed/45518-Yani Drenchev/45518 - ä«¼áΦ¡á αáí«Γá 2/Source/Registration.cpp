//
// Created by Yani Drenchev on 6.05.21.
//

#include "../Headers/Registration.h"

Registration::Registration(const std::string &registration) {
    bool isCorrect = true;
    isCorrect = checkRegistration(registration);
    if (!isCorrect) {
        throw std::invalid_argument("Invalid registration number");
    }
    this->registration = registration;
}

bool Registration::checkRegistration(const std::string &registration) {
    if (registration.size() == 7 || registration.size() == 8) {
        if (isalpha(registration[0]) && isalpha(registration[1])
            && isdigit(registration[2]) && isdigit(registration[3]) && isdigit(registration[4]) &&
            isdigit(registration[5]) && isalpha(registration[6]) && isalpha(registration[7])) {
            return true;
        } else if (isalpha(registration[0])
                   && isdigit(registration[1]) &&
                   isdigit(registration[2]) && isdigit(registration[3]) &&
                   isdigit(registration[4]) &&
                   isalpha(registration[5]) && isalpha(registration[6])) {
            return true;
        }
    }
    return false;
}

std::string Registration::getRegistration() const {
    return registration;
}

bool Registration::operator==(const Registration &oth) const {
    if (this->registration == oth.registration) {
        return true;
    }
    return false;
}


Registration::Registration() {
    registration = " ";
}
