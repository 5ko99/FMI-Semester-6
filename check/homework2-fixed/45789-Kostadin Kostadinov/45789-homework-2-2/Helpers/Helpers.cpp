#include "Helpers.hpp"  
	
bool isEqualString(std::string str_1, std::string str_2) {
    if (str_1 == str_2) return true;
    if (str_1.size() != str_2.size()) return false;
    size_t len = str_1.size();
    const char* ch_1 = str_1.c_str();
    const char* ch_2 = str_2.c_str();
    for (size_t i = 0; i < len; i++) {
        if (std::toupper(ch_1[i]) != std::toupper(ch_2[i])) return false;
    } 
    return true;
}

unsigned strToInt(const std::string str) {
    unsigned buffer = 0;
    for(size_t i = 0; i < str.size(); i++) {
        buffer *= 10;
        buffer += (str[i] - '0');
    }
    return buffer;
}

std::string intToStr(const unsigned num) {
    std::string buffer;
    unsigned buf=num;
    while (buf != 0) {
        buffer.insert(0, 1, ((buf % 10) + '0'));
        buf /= 10;
    }
    return buffer;
}
