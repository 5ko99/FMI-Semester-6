

#ifndef HW2_REGISTRATION_H
#define HW2_REGISTRATION_H
# include <string>

class Registration {
private:
    std::string registration;
public:
    Registration();
    Registration(const std::string&);
    Registration& operator= (const std::string&);
    void print()const;
    std::string getRegistration()const;
   
};

#endif //HW2_REGISTRATION_H
