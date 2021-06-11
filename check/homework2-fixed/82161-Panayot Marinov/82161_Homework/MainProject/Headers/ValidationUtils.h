#pragma once
#ifndef VALIDATIONUTILS_H
#define VALIDATIONUTILS_H

class ValidationUtils {
public:
    static bool isValidNumberPlate(const char* registrationString);
    static bool isValidId(const char* id);
    static bool isLetter(const char symbol);
    static bool isDigit(const char symbol);
};

#endif /*VALIDATIONUTILS_H*/
