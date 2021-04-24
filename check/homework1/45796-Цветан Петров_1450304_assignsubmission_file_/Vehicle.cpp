#include "Header.h"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space) {

	RegNumber = registration;
	descr = description;
	capacity = space;
	
}

const char* Vehicle::registration() const {
	unsigned size = RegNumber.getLenght() + 1;
	char* temp = new(std::nothrow) char[size];
	if (temp != nullptr) {
		for (unsigned i = 0; i < size - 1; i++) {
			temp[i] = RegNumber[i];
		}

		temp[size - 1] = '\0';
	}

	return temp;
}

std::size_t Vehicle::space() const {

	return capacity;
}

const char* Vehicle::description() const {

	unsigned size = descr.getLenght() + 1;
	char* temp = new(std::nothrow) char[size];
	if (temp != nullptr) {
		for (unsigned i = 0; i < size - 1; i++) {
			temp[i] = descr[i];
		}

		temp[size - 1] = '\0';
	}

	return temp;
}