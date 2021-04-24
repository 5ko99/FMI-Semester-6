#include <iostream>
#include <cstring>
#include "Vehicle.h"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space=1):
	regNum(registration),dscrp(description),parkSpace(space) {
	if (space == 0) //it's not logically possible ...
	{//in program we can not input 0 anyway
		parkSpace = 1;
	}
}



Vehicle::Vehicle(const Vehicle& newVeh) {
	regNum = newVeh.regNum;
	dscrp = newVeh.dscrp;
	parkSpace = newVeh.parkSpace;
}

const char*  Vehicle::registration() const {
	return regNum.c_str();
}
const char* Vehicle::description() const {
	return dscrp.c_str();
}
std::size_t Vehicle::space() const {
	return parkSpace;
}
Vehicle::~Vehicle() {
	regNum.clear();
	dscrp.clear();
	parkSpace = 0;
}

bool Vehicle::operator==(const Vehicle& other) const {
	return (dscrp == other.dscrp && regNum == other.regNum && parkSpace == other.parkSpace);
}
void Vehicle::printInfo() const {
	std::cout << "(Reg:)" << regNum << " ;(Info:)" << dscrp << " ;(Space:)" << parkSpace<<std::endl;
}

