#include "RegistrationNumber.h"

Result<RegistrationNumber> RegistrationNumber::isValid(std::string str) {
	trim(str);

	if (str.size() != 7 && str.size() != 8) {
		return Result<RegistrationNumber> { false };
	}

	bool isValid1 = isLetter(str[0]) &&
		isNumber(str[1]) && isNumber(str[2]) && isNumber(str[3]) && isNumber(str[4]) &&
		isLetter(str[5]) && isLetter(str[6]);

	if (isValid1) {
		RegistrationNumber regNumber = RegistrationNumber{ str.substr(0, 1),
														   str.substr(1, 4),
														   str.substr(5, 6) };

		return Result<RegistrationNumber> { true, regNumber };
	}

	bool isValid2 = isLetter(str[0]) && isLetter(str[1]) &&
		isNumber(str[2]) && isNumber(str[3]) && isNumber(str[4]) && isNumber(str[5]) &&
		isLetter(str[6]) && isLetter(str[7]);

	if (isValid2) {
		RegistrationNumber regNumber = RegistrationNumber{ str.substr(0, 2),
														   str.substr(2, 4),
														   str.substr(6, 7) };

		return Result<RegistrationNumber> { true, regNumber };
	}

	return Result<RegistrationNumber> { false };
}

bool operator== (RegistrationNumber a, RegistrationNumber b) {
	return a.prefix == b.prefix &&
		a.infix == b.infix &&
		a.suffix == b.suffix;
}

std::ostream& operator<< (std::ostream& out, RegistrationNumber a) {
	out << a.prefix + a.infix + a.suffix;

	return  out;
}
