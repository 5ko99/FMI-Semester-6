#ifndef REGISTRATION_EXCEPTION_H
#define REGISTRATION_EXCEPTION_H

#include <string>

class RegistrationException : public std::exception {
    private:
        std::string message;
    public:
        RegistrationException(const std::string& message);
        const char* what() const throw();
};

#endif
