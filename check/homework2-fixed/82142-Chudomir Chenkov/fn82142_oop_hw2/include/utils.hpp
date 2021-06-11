#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>
#include <vector>

void ltrim(std::string &str);
void rtrim(std::string &str);
std::string to_lowercase(const std::string &str);
std::vector<std::string> split(std::string str, char delim = ' ');
bool is_number(const std::string &str);

#endif // _UTILS_HPP_
