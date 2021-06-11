#include "Utils.h"
bool isLetter(char ch) {
	if (ch >= 'A' && ch <= 'Z') {
		return true;
	}

	return false;
}

bool isNumber(char ch) {
	if (ch >= '0' && ch <= '9') {
		return true;
	}

	return false;
}

void trim(std::string& str) {
	while (*str.begin() == ' ' && !str.empty()) {
		str.erase(str.begin());
	}
}

Result<std::string> getStringInQuotes(std::string& str) {
	str.erase(str.begin());
	std::string word = "";
	size_t i = 0;
	for (char ch : str) {
		if (ch == '"') {
			break;
		}

		word += ch;
		i++;
	}
	str.erase(str.begin(), std::next(str.begin(), i));

	if (str.size() == 0) {
		return Result<std::string> { false };
	}
	else if (str[0] == '"') {
		str.erase(str.begin());
	}

	return Result<std::string> { true, word };
}

Result<std::string> getWord(std::string& str) {
	trim(str);
	std::string word = "";

	if (*str.begin() == '"') {
		return getStringInQuotes(str);
	}

	size_t i = 0;
	for (char ch : str) {
		if (ch == ' ') {
			break;
		}

		word += ch;
		i++;
	}
	str.erase(str.begin(), std::next(str.begin(), i));

	if (word.size() == 0) {
		return Result<std::string> { false };
	}

	return Result<std::string> { true, word };
}
