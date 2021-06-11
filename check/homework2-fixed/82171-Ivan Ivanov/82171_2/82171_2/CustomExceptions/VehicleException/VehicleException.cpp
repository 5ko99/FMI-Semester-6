#include "VehicleException.h"

VehicleException::VehicleException(const std::string& message) :
    message(message) {
        ;
}

const char* VehicleException::what() throw () {
     return message.c_str();
}
