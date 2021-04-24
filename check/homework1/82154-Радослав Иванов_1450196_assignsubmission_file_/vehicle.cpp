#include "vehicle.h"

//Constructor
Vehicle::Vehicle(const char* reg, const char* descr, size_t space) : 
                regNumber(reg), descript(descr), requiredSpace(space) {}

//Other methods
const char* Vehicle::registration() const {return regNumber.c_str();}

const char* Vehicle::description() const {return descript.c_str();}

size_t Vehicle::space() const {return requiredSpace;}