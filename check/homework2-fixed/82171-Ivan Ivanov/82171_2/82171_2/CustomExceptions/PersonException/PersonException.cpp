#include "PersonException.h"

PersonException::PersonException(const std::string& message) :
    message(message) {
        ;
}

const char* PersonException::what() const throw() {
     return message.c_str();
}
