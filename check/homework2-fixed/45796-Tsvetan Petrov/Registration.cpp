#include "Registration_Header.h"

void Registration::copy(const std::string str)
{
		unsigned size = str.length();
		char temp[9];
		if (size < 7 || size > 8) {
			throw std::exception(" ");
		}

		if (!(isalpha(str[0]))) {
			throw std::exception(" ");
		}
		else {
			temp[0] = str[0];
		}

		if (isalpha(str[1])) {
			temp[1] = str[1];
			for (unsigned i = 2; i < 6; i++) {
				if (!(isdigit(str[i]))) {
					throw std::exception(" ");
				}
				else {
					temp[i] = str[i];
				}
			}

			if (!(isalpha(str[6])) || !(isalpha(str[7]))) {
				throw std::exception(" ");
			}
			else {
				temp[6] = str[6];
				temp[7] = str[7];
				temp[8] = '#';
			}
		}
		else if (isdigit(str[1])) {
			temp[1] = str[1];
			for (unsigned i = 2; i < 5; i++) {
				if (!(isdigit(str[i]))) {
					throw std::exception(" ");
				}
				else {
					temp[i] = str[i];
				}
			}

			if (!(isalpha(str[5])) || !(isalpha(str[6]))) {
				throw std::exception(" ");
			}
			else {
				temp[5] = str[5];
				temp[6] = str[6];
				temp[7] = '#';
			}

		}

		for (unsigned i = 0; i < 9; i++) {
			reg_number[i] = temp[i];
		}
}

Registration::Registration(const std::string str)
{

	copy(str);

}

Registration& Registration::operator=(const char* str) {
	copy(str);
	return *this;
}

bool Registration::operator==(const char* str) const {

	unsigned index = 0;
	unsigned count = 0;
	while (reg_number[index] != '#') {
		if (reg_number[index] == str[index]) {
			index++;
			count++;
		}
		else {
			return false;
		}
	}
	if (count == strlen(str)) {
		return true;
	}
	else {
		return false;
	}

}

const char* Registration::toString() const {
	char* temp = new(std::nothrow) char[9];
	unsigned index = 0;
	if (temp != nullptr) {
		while (reg_number[index] != '#') {
			temp[index] = reg_number[index];
			index++;
		}
		temp[index] = '\0';
	}
	return temp;
}
