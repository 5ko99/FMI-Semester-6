#include "Utils.h"

#include <algorithm>

uint32_t Utils::GetNumberLength(int64_t n)
{
    uint32_t cnt = 0;
    do {
        ++cnt; 
        n /= 10;
    } while (n);
    
    return cnt;
}

bool Utils::ValidateCarId(const std::string& id)
{
    if (id.size() != 8 && id.size() != 7)
        return false;
    std::string cpy = id;
    std::transform(cpy.begin(), cpy.end(), cpy.begin(), ::tolower);
    if (!std::isalpha(cpy[0]))
        return false;
    uint32_t startIdx;
    if (std::isdigit(cpy[1]))
        startIdx = 1;
    else
        startIdx = 2;
    for (uint32_t i = startIdx; i < startIdx + 4; i++)
        if (!std::isdigit(cpy[i])) return false;
    startIdx += 4;
    
    if (!std::isalpha(cpy[startIdx]) || !std::isalpha(cpy[startIdx + 1]))
        return false;
    return true;
}

// https://stackoverflow.com/a/37454181
std::vector<std::string> Utils::SplitString(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}
