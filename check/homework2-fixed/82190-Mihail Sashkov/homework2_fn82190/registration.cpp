#include"registration.h"
#include<stdexcept>
#include<iostream>


Registration::Registration(std::string registration) {

    if(registration.length() > 8 || registration.length() < 7) {            //checks for the length of the registration number
        throw std::length_error("The length  of registration is invalid!");
    }

    if(registration.length() == 7) {                              //check if the symbols are rigth in the registration number

        if(!((registration[0] >= 'A' && registration[0] <= 'Z') &&
            (registration[1] >= '0' && registration[1] <='9') &&
            (registration[2] >= '0' && registration[2] <='9') &&
            (registration[3] >= '0' && registration[3] <='9') &&
            (registration[4] >= '0' && registration[4] <='9') &&
            (registration[5] >= 'A' && registration[5] <= 'Z') &&
            (registration[6] >= 'A' && registration[6] <= 'Z'))) {

                throw std::invalid_argument("The registration is incorrect!");

        }

    }

    if(registration.length() == 8) {                          //check if the symbols are rigth in the registration number

        if(!((registration[0] >= 'A' && registration[0] <= 'Z') &&
            (registration[1] >= 'A' && registration[1] <= 'Z') &&
            (registration[2] >= '0' && registration[2] <= '9') &&
            (registration[3] >= '0' && registration[3] <= '9') &&
            (registration[4] >= '0' && registration[4] <= '9') &&
            (registration[5] >= '0' && registration[5] <= '9') &&
            (registration[6] >= 'A' && registration[6] <= 'Z') &&
            (registration[7] >= 'A' && registration[7] <= 'Z'))) {

                throw std::invalid_argument("The registration is incorrect!");

        }

        }

    this->registration = registration;

}


std::string Registration::getRegistration() const{
    return registration;
}
