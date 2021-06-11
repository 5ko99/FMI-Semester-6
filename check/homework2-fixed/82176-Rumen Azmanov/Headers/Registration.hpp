#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP

#include <iostream>
#include <cstring>
#include <vector>

bool isARegistration(const char regNumberInput[9]);

class Registration {
   private:
    char regNumber[9];
    static std::vector<std::string> registrations;

   public:
    //! Registration constructor
    Registration();
    Registration(const char regNumberInput[9]);

    //! Copy assignment operator
    Registration& operator=(const Registration& other);

    const char* getRegistration() const;

    //! Registration destructor
    ~Registration();
};

#endif
