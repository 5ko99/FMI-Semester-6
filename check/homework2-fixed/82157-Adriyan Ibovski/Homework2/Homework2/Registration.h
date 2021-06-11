#pragma once
#include <string>
using std::string;

class Registration{
private:
    string m_reg;

public:
    static bool checkReg(const string& reg);
    explicit Registration(const string& reg);
    ~Registration();
    Registration(const Registration& other);
    string getString() const;
    bool operator==(const Registration& other);
};
