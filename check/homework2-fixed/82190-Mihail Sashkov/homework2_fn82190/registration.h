
#ifndef REGISTRATION
#define REGISTRATION

#include<string>

class Registration {
private:
    std::string registration;

public:
    Registration(std::string registration);   //constructor for registration
    std::string getRegistration() const;      //getter for the registration number

};

#endif
