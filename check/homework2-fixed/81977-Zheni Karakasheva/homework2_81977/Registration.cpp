#include "Registration.h"

bool Registration::isValidLetter(char current) {
    return current <= 'Z' && current >= 'A';
}

bool Registration::isDigit(char current) {
    return current <= '9' && current >= '0';
}

//a registration number is valid if the length is 7 or 8 characters(depends on the town's letter/letters),
//the last two characters are capital letters,
//before them are 4 digits and a capital letter
//and then either the length is 7 or the character is also a capital letter
bool Registration::isValidRegNumber(const char* otherRegistration) {
    std::size_t length = strlen(otherRegistration);

    return (length >= 7 && length <= 8) && (isValidLetter(otherRegistration[length-1]) && isValidLetter(otherRegistration[length-2])) 
           && isDigit(otherRegistration[length-3]) && isDigit(otherRegistration[length-4])
           && isDigit(otherRegistration[length-5]) && isDigit(otherRegistration[length-6]) 
           && isValidLetter(otherRegistration[length-7]) 
           && (length == 7 || isValidLetter(otherRegistration[length-8]));
}

//if valid - creates a registration number
//else throws an error with the message indicating an invalid format
Registration::Registration(const char* otherRegistration) {
    if(isValidRegNumber(otherRegistration)) {
        strcpy(registrationNumber, otherRegistration);
    } else {
        throw std::invalid_argument("The registration number is invalid!");
    }
}

const char* Registration::getRegNumber() const {
    return registrationNumber;
}

bool Registration::operator==(const Registration& otherRegistration) const {
    return strcmp(registrationNumber,otherRegistration.registrationNumber) == 0;
}

