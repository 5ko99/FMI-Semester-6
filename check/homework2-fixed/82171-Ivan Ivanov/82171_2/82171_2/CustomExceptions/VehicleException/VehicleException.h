#ifndef VEHICLE_EXCEPTION_H
#define VEHICLE_EXCEPTION_H

#include <string>

class VehicleException : public std::exception {
    private:
        std::string message;
    public:
        VehicleException(const std::string& message);
        const char* what() throw ();
};

#endif
