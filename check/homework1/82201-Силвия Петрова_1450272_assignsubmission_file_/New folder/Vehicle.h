#pragma once

#include "MyString.h"

/*! Vehicle - превозно средство */
class Vehicle
{
public:
    //Класът ДА НЯМА default constructor
    Vehicle(const char *registration, const char *description, std::size_t space);

    const char *registration() const; //!< Връща регистрационния номер като C-style символен низ.
    const char *description() const;  //!< Връща описанието на превозното средство като C-style символен низ.
    std::size_t space() const;        //!< Връща мястото, което заема превозното средство при паркиране.

private:
    MyString licence;              //!< регистрационен номер -- символен низ (използвайте типа MyString).*/
    MyString description1;         //!< описание -- символен низ (използвайте типа MyString).*/
    std::size_t numOfParkingSpots; //!< брой места за паркиране, които заема превозното средство -- стойност от тип std::size_t.*/
};