#pragma once

#include <regex>
#include <vector>
#include <string>
#include <vector>

class Registration
{
public:
    Registration(const std::string &regNum);
    std::string getRegistration() const;

private:
    static std::string validateRegNum(const std::string &regNum);
    const std::string regNum;
};

template <typename T>
T checkUniqueness(const T &arg)
{
    static std::vector<T> vector;
    for (T item : vector)
    {
        if (item == arg)
            throw std::runtime_error("This item is already used");
    }
    vector.push_back(arg);
    return arg;
}
