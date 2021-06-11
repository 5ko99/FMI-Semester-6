#ifndef RegistrationNumber_h
#define RegistrationNumber_h

#include <stdio.h>
#include "Utils.h"

struct RegistrationNumber {
	std::string prefix, infix, suffix;

	static Result<RegistrationNumber> isValid(std::string);
};

bool operator== (RegistrationNumber a, RegistrationNumber b);

std::ostream& operator<< (std::ostream& out, RegistrationNumber a);

#endif /* RegistrationNumber_h */
