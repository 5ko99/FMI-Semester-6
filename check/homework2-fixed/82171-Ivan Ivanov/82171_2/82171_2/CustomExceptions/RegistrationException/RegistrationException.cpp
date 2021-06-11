#include "RegistrationException.h"

RegistrationException::RegistrationException(const std::string& message) :
    message(message) {
        ;
}

const char* RegistrationException::what() const throw() {
     return message.c_str();
}
