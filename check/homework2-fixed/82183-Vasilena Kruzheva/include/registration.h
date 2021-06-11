#ifndef REGISTRATION_H
#define REGISTRATION_H

/**
* \brief Class holding vehicle's registration
* \author V. Krazheva
*/


class Registration
{
private:
    static const int REGISTRATION_LENGTH = 8;   //!< stores the length of the registration
    char registration[REGISTRATION_LENGTH + 1]; //!< stores the registration

public:
     /**
     * Takes a char array and checks whether it's a valid registration
     * 
     * @param reg is char array to be validated
     * @return Returns true if the array is a valid registration and false otherwise
     */
    static bool validate(const char* reg);
    
    ///Constructor for creating a Registration object
    Registration(const char* reg);

    ///Constructor creating a Registration object with the same registration as other's
    Registration(const Registration& other);

    ///Operator= is deleted because a registration shouldn't be changed
    Registration& operator=(const char* reg) = delete;
    
    ///Operator= other is not deleted because it's used when copying objects that use the Registration class
    Registration& operator=(const Registration& other);

    ///Returns the stored registration
    const char* getRegistration();

};

#endif
