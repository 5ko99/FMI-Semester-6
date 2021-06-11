#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <string>
#include <iostream>
#include <cstring>

class Registration {
    private:
        char registration[9];

        static const std::size_t MIN_LENGTH = 7;
        static const std::size_t MAX_LENGTH = 8;
        static const std::size_t NUM_ENDING_LETTERS = 2;
        static const std::size_t NUM_DIGITS = 4;
        const static bool isLetter(char c);
        const static bool isDigit(char c);
    public:
        Registration(std::string registration);

        // copy constructor
        Registration(const Registration& other);

        // copy operator
        Registration* operator=(const Registration& other);

        // chacks if a registration value is valid
        // 'letter' + ('letter') + NUM_DIGITS * digits + NUM_ENDING_LETTERS * letters
        // should be called before creating object
        static const bool isValid(std::string registration);

        bool operator==(const Registration& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Registration& registration);
};

#endif
