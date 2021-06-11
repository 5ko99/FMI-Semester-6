#pragma once
#include <string>

class Registration
{
public:
    Registration();
    Registration(const std::string& data);
    //bool isValid(const std::string& data) const;
    std::string getData() const;
    friend bool operator ==(const Registration& lhs, const Registration& rhs);
    friend std::ostream& operator <<(std::ostream& out, const Registration& r);
    friend std::istream& operator >>(std::istream& in, Registration& r);

private:
    std::string data;
};
