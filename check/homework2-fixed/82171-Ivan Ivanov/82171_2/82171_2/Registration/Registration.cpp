#include "Registration.h"

Registration::Registration(std::string registration) {
    const char* regChar = registration.c_str();
    strcpy(this->registration, regChar);
}

Registration::Registration(const Registration& other) {
    strcpy(this->registration, other.registration);
}

Registration* Registration::operator=(const Registration& other) {
    if (this == &other) {
        return this;
    }

    strcpy(this->registration, other.registration);
    return this;
}

const bool Registration::isDigit(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }

    return false;
}

const bool Registration::isLetter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return true;
    }

    return false;
}

bool const Registration::isValid(std::string registration) {
    if (registration.size() < MIN_LENGTH || registration.size() > MAX_LENGTH) {
        return false;
    }

    for (std::size_t i = registration.size() - 1; i >= registration.size() - NUM_ENDING_LETTERS; --i) {
        if (!isLetter(registration[i])) {
            return false;
        }
    }

    for (std::size_t i = registration.size() - NUM_ENDING_LETTERS - 1; i >= registration.size() - NUM_ENDING_LETTERS - NUM_DIGITS; --i) {
        if (!isDigit(registration[i])) {
            return false;
        }
    }

    for (int i = registration.size() - NUM_ENDING_LETTERS - NUM_DIGITS - 1; i >= 0; --i) {
        if (!isLetter(registration[i])) {
            return false;
        }
    }

    return true;
}

bool Registration::operator==(const Registration& other) const {
    return (strcmp(this->registration, other.registration) == 0);
}

std::ostream& operator<<(std::ostream& os, const Registration& registration) {
    os << registration.registration;
    return os;
}
