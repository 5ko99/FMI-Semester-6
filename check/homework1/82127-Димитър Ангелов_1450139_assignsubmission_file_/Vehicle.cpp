#include "Vehicle.h"

#include <new>
#include <cstring>
#include <stdexcept>
#include <cassert>


//Vehicle::Vehicle(){
//
//    MyString a('\0');
//    MyString b('\0');
//    this->rg=a;
//    this->descr=b;
//    this->big=0;
//}

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space){

    MyString a(registration);
    MyString b(description);
    this->rg=a;
    this->descr=b;
    this->big=space;
}

Vehicle& Vehicle::operator=(const Vehicle& car){

        this->rg=car.rg;
        this->descr=car.descr;
        this->big=car.big;

        return *this;
    }

const char* Vehicle::registration()const{

    MyString a;
    a=this->rg;
    return a.c_str();

}

const char* Vehicle::description()const{

    MyString a;
    a=this->descr;
    return a.c_str();

}

std::size_t Vehicle::space()const{

    return this->big;

}

