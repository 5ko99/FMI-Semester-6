#include "../Headers/Registration.h"

#include <stdexcept>

//void Registration::validate(char *registrationNumber) const {
void Registration::validate(const std::string &registrationNumber) const {

    // Examples:
    // C1234AB, XY1111YX are valid
    // 111145, ABC34DEF, C11D are NOT valid

    const unsigned VALID_LENGTH_0 = 7;
    const unsigned VALID_LENGTH_1 = 8;

    // Some magic numbers now... No regex
    switch (registrationNumber.size()) {
        case VALID_LENGTH_0:
            if (!std::isalpha(registrationNumber[0]) ||
                !std::isalpha(registrationNumber[5]) ||
                !std::isalpha(registrationNumber[6])) {
                throw std::invalid_argument("Invalid registration number! First char must be a letter!");
            }

            // All letters have to be uppercase
            if (!std::isupper(registrationNumber[0]) ||
                !std::isupper(registrationNumber[5]) ||
                !std::isupper(registrationNumber[6])) {
                throw std::invalid_argument("Invalid registration number! All letters must be uppercase ");
            }

            for (int i = 1; i <= 4; ++i) {
                if (std::isalpha(registrationNumber[i])) {
                    throw std::invalid_argument("Invalid registration number! Letter on the position for integer!");
                }
            }
            break;

        case VALID_LENGTH_1:
            if (!std::isalpha(registrationNumber[0]) ||
                !std::isalpha(registrationNumber[1]) ||
                !std::isalpha(registrationNumber[6]) ||
                !std::isalpha(registrationNumber[7])) {
                throw std::invalid_argument("Invalid registration number! First char should be a letter!");
            }

            // All letters have to be uppercase
            if (!std::isupper(registrationNumber[0]) ||
                !std::isupper(registrationNumber[1]) ||
                !std::isupper(registrationNumber[6]) ||
                !std::isupper(registrationNumber[7])) {
                throw std::invalid_argument("Invalid registration number! All letters must be uppercase ");
            }

            for (int i = 2; i <= 5; ++i) {
                if (std::isalpha(registrationNumber[i])) {
                    throw std::invalid_argument("Invalid registration number! Letter on the position for integer!");
                }
            }
            break;

        default:
            throw std::invalid_argument("Invalid registration number!");
    }
}

Registration::Registration(const std::string &registrationNumber) {
    validate(registrationNumber);
    m_registrationNumber = registrationNumber;
//    strcpy(m_registrationNumber, registrationNumber);
}


bool Registration::operator==(const Registration &rhs) const {
    return m_registrationNumber == rhs.m_registrationNumber;
//    return strcmp(m_registrationNumber, rhs.m_registrationNumber) == 0;
}

std::ostream &operator<<(std::ostream &out, const Registration &registration) {
    out << registration.m_registrationNumber;
    return out;
}
