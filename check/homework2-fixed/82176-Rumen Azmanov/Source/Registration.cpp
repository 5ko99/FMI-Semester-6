#include "..\Headers\Registration.hpp"

std::vector<std::string> Registration::registrations;

bool isARegistration(const char registration[9]) {
    if (strlen(registration) == 8 &&
        (registration[0] >= 'A' && registration[0] <= 'Z') &&
        (registration[1] >= 'A' && registration[1] <= 'Z') &&
        (registration[2] >= '0' && registration[2] <= '9') &&
        (registration[3] >= '0' && registration[3] <= '9') &&
        (registration[4] >= '0' && registration[4] <= '9') &&
        (registration[5] >= '0' && registration[5] <= '9') &&
        (registration[6] >= 'A' && registration[6] <= 'Z') &&
        (registration[7] >= 'A' && registration[7] <= 'Z')) {
        return true;
    } else {
        return false;
    }
}

Registration::Registration() {
    regNumber[0] = '\0';
}

Registration::Registration(const char regNumberInput[9]) {
    bool appear = false;
    if (isARegistration(regNumberInput)) {
        for (int i = 0; i < registrations.size(); ++i) {
            if (std::strcmp(regNumberInput, registrations.at(i).c_str()) == 0) {
                appear = true;
                throw std::invalid_argument("[!] Vehicle with the same number already exists!\n");
            }
        }
    } else {
        throw std::invalid_argument("[!] Not a registration number!\n");
    }

    if (appear == false) {
        strcpy(regNumber, regNumberInput);
        regNumber[8] = '\0';
        registrations.push_back(regNumberInput);
    }
}

Registration& Registration::operator=(const Registration& other) {
    if (this != &other) {
        std::strcpy(regNumber, other.getRegistration());
    }
    return *this;
}

const char* Registration::getRegistration() const {
    return regNumber;
}

Registration::~Registration() {
}
