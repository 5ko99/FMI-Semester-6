#pragma once

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

using std::invalid_argument;
using std::ostream;
using std::string;

class Registration {
  private:
    string data = "";

  public:
    Registration() = delete;

    Registration(const string& str);
    Registration(const Registration& other);

    const char* str() const;
    bool operator==(const Registration& other) const;
    bool operator==(const char* other) const;

    friend ostream& operator<<(ostream& os, const Registration& r);
};
