#include "EndException.h"

EndException::EndException(const std::string& message) :
    message(message) {
        ;
}

const char* EndException::what() const throw() {
     return message.c_str();
}
