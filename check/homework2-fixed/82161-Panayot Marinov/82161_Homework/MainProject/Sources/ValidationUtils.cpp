#include "../Headers/ValidationUtils.h"
#include "../Headers/Constants.h"
#include <cstring>
#include <iostream>

bool ValidationUtils::isValidNumberPlate(const char* registrationString) {    
    //Case 1 it has one letter at the beginning
    bool validCase1 = true;

    //The length is not correct
    if(registrationString[PLATE_ONE_FRONT_LETTER_LENGTH] != '\0')
        validCase1 = false;

    if(!isLetter(registrationString[0]))
        validCase1 = false;

    for (size_t i = 1; i < 5; i++) {
        if(!isDigit(registrationString[i]))
            validCase1 = false;
    }

    for (size_t i = 5; i < PLATE_ONE_FRONT_LETTER_LENGTH; i++) {
        if(!isLetter(registrationString[i]))
            validCase1 = false;
    }


    //Case 2 it has two letter at the beginning
    bool validCase2 = true;

    //The length is not correct
    if(registrationString[PLATE_TWO_FRONT_LETTERS_LENGTH] != '\0')
        validCase2 = false;

    for (size_t i = 0; i < 2; i++) {
        if(!isLetter(registrationString[i]))
            validCase2 = false;
    }

    for (size_t i = 2; i < 6; i++) {
        if(!isDigit(registrationString[i]))
            validCase2 = false;
    }

    for (size_t i = 6; i < PLATE_TWO_FRONT_LETTERS_LENGTH; i++) {
        if(!isLetter(registrationString[i]))
            validCase2 = false;
    }

    return validCase1 || validCase2;
}

bool ValidationUtils::isValidId(const char* id) {
    bool valid = true;
    size_t idLen = strlen(id);
    if(idLen == 0)
        return false;

    if(idLen > MAX_ID_LENGTH) {
        valid = false;
    }

    for (size_t i = 0; i < idLen; i++) {
        if(!isDigit(id[i])) {
            valid = false;
            break;
        }
    }
    
    return valid;
}

bool ValidationUtils::isLetter(const char symbol) {
    bool isCapitalLetter = (symbol >= 'A') && (symbol <= 'Z');
    //bool isNonCapitalLetter = (symbol >= 'a') && (symbol <= 'z');

    return isCapitalLetter/* || isNonCapitalLetter*/;
}

bool ValidationUtils::isDigit(const char symbol) {
    return (symbol >= '0' && symbol <= '9');
}
