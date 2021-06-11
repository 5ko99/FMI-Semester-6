#include <iostream>
#include "MyHeader.h"

int main() {

	return 0;
}
Registration::Registration(const char* str) {
	if (!isValid(str)) {
		throw std::exception();
	}
}

bool Registration::isValid(const char* str) {
	unsigned len = strlen(str);
	size_t i = 0;
	if ((len > 6 && len < 9) && isalpha(str[i])) {
		++i;
		if (isalpha(str[i])) {
			++i;
			for (size_t j = i; j < i + 4; ++j) {
				if (!isdigit(str[j])) {
					return false;
				}
			}
			i = i + 4;
			for (size_t j = i; j < i + 2; ++j) {
				if (!isalpha(str[j])) {
					return false;
				}
			}
			return true;
		}
		else if (isdigit(str[i])) {
			for (size_t j = i; j < i + 4; ++j) {
				if (!isdigit(str[j])) {
					return false;
				}
			}
			i = i + 4;
			for (size_t j = i; j < i + 2; ++j) {
				if (!isalpha(str[j])) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}

	}
}
size_t Registration::MAXSIZE() const {
	return MAX_SIZE;
}
Person::Person(std::string str, unsigned int id)
	:name(str), id(id)
{
}
