#include "Registration.h"

Registration::Registration() {
	this->regis = "";
}

Registration::Registration(std::string str) {
	this->regis = str;
	if (this->regis.size() > 8 || this->regis.size() < 7) {
		throw "invalid registration";
	}
	if (this->regis.size() == 7) {
		if (!isalpha(this->regis[0]) || !isalpha(this->regis[5]) || !isalpha(this->regis[6])) {
			throw "invalid registration";
		}
		if (!isdigit(this->regis[1]) || !isdigit(this->regis[2]) || !isdigit(this->regis[3]) || !isdigit(this->regis[4])) {
			throw "invalid registration";
		}
	}
	if (this->regis.size() == 8) {
		if (!isalpha(this->regis[0]) || !isalpha(this->regis[1]) || !isalpha(this->regis[6]) || !isalpha(this->regis[7])) {
			throw "invalid registration";
		}
		if (!isdigit(this->regis[2]) || !isdigit(this->regis[3]) || !isdigit(this->regis[4]) || !isdigit(this->regis[5])) {
			throw "invalid registration";
		}
	}
}


Registration::Registration(const Registration& other) {
	this->regis = other.regis;
}

Registration Registration::operator=(Registration& other) {
	this->regis = other.regis;
	return *this;
}

std::string Registration::getReg() const {
	return this->regis;
}

void Registration::print() const {
	std::cout << this->regis << std::endl;
}

bool operator==(const Registration& lhs, const Registration& rhs) {
	if (lhs.getReg() != rhs.getReg()) {
		return false;
	}
	return true;
}


