#include "../Headers/Registration.h"

Registration::Registration(const std::string &registration) : registration(std::move(registration)) {}

Registration::Registration(const Registration &object) {
    this->registration = object.registration;
}

const std::string &Registration::getRegistration() const {
    return this->registration;
}

Registration &Registration::operator=(const Registration &object) {
    if (this != &object) {
        this->registration = object.registration;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Registration &object) {
    os << " Registration: " << object.getRegistration() << std::endl;

    return os;
}
