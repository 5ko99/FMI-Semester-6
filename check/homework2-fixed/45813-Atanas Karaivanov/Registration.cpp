#include "Registration.h"

Registration::Registration() {
	strcpy_s(registration, 9, "");
}

bool Registration::isValid(const char* str) const {
	if (isalpha(str[0]) != 0 && isalpha(str[1]) != 0 && isalpha(str[6]) != 0 && isalpha(str[7]) != 0
		&& isdigit(str[2]) != 0 && isdigit(str[3]) != 0 && isdigit(str[4]) != 0 && isdigit(str[5]) != 0) {

		if (str[8] != '\0') {
			return false;
		}

		return true;
	}
	if (isalpha(str[0]) != 0 && isalpha(str[5]) != 0 && isalpha(str[6]) != 0
		&& isdigit(str[1]) != 0 && isdigit(str[2]) != 0 && isdigit(str[3]) != 0 && isdigit(str[4]) != 0) {

		if (str[7] != '\0') {
			return false;
		}

		return true;
	}

	return false;
}

Registration::Registration(const char* str) {
	if (isValid(str) == true) {
		strcpy_s(this->registration, 9, str);
	}
	else {
		throw exception("Invalid registration!");
	}
}

Registration& Registration::operator=(const char* str) {
	if (isValid(str) == true) {
		if (strcmp(this->registration, str) != 0) {
			strcpy_s(this->registration, 9, str);
		}
		return *this;
	}
	else {
		throw exception("Invalid registration!");
	}
}

bool Registration::operator==(const Registration& reg) {
	if (strcmp(this->registration, reg.getReg()) == 0) {
		return true;
	}
	return false;
}

const char* Registration::getReg() const {
	return this->registration;
}


