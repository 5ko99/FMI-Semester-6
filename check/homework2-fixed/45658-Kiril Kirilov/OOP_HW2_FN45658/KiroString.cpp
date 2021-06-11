#include "KiroString.h"

std::vector<std::string> tokenizer(std::string str) {
    std::vector<std::string> result;
    int start = 0;
    int end = 0;
    while (end != -1) {
        if (str[start] == '"') {
            end = str.find("\"", start + 1);
            result.push_back(str.substr(start, end + 1 - start));
            start = str.find(" ", end) + 1;
        }
        else {
            end = str.find(' ', start);
            result.push_back(str.substr(start, end - start));
            start = end + 1;
        }
    }
    return result;
}

void toUpperCase(std::string& str)
{
    size_t size = str.size();
    for (size_t i = 0; i < size; ++i) {
        str[i] = (char)toupper(str[i]);
    }
}

