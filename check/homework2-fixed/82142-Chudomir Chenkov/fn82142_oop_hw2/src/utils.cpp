#include "utils.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>

void ltrim(std::string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char c) {
      return !std::isspace(c);
    }));
}

void rtrim(std::string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char c) {
      return !std::isspace(c);
    }).base(), str.end());
}

std::string to_lowercase(const std::string& str) {
    std::string res = str;

    std::transform(res.begin(), res.end(), res.begin(), ::tolower);

    return res;
}

std::vector<std::string> split(std::string str, char delim) {
    std::vector<std::string> ret;
    std::size_t pos;

    /* Trim spaces on both sides */
    ltrim(str);
    rtrim(str);

    while ((pos = str.find(delim)) != std::string::npos) {
        ret.push_back(str.substr(0, pos));

        while (str.at(pos) == delim) pos++;

        str.erase(0, pos);
    }

    ret.push_back(str);

    return ret;
}

/* Not quite sure if C++14 is allowed */
//std::vector<std::string> split(std::string str, char delim) {
//    std::vector<std::string> res;
//    std::string s;
//
//    ltrim(str);
//    rtrim(str);
//
//    std::istringstream iss(str);
//
//    while (iss >> std::quoted(s)) {
//        res.push_back(s);
//    }
//
//    return res;
//}

bool is_number(const std::string& str) {
    return !str.empty() && std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isdigit(c); }) == str.end();
}
