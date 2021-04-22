#define CATCH_CONFIG_MAIN
#include <cstring>
#include "catch2.hpp"
#include "myString.h"
#include "vehicle.h"
#include "garage.h"

TEST_CASE ("constructors") {
    
    Garage test(2);
    Garage test2(test);
    
    CHECK(test.getCapacity() == 2);
    CHECK(test2.getCapacity() == 2);
   
}

TEST_CASE ("insert, erase, operator=, operator[], at, find, size, empty") {

    Vehicle car ("1234", "benz", 1);
    Vehicle bmw ("1235", "bmw", 2);
    Garage test(3);

  
    test.insert(car);
    CHECK(!strcmp(test[0].getRegistration(), car.getRegistration()));
    
    Garage test2 = test;

    CHECK(!strcmp(test2[0].getRegistration(), car.getRegistration()));
    
    test2.insert(bmw);
    CHECK(!strcmp((test2.at(1)).getRegistration(), bmw.getRegistration()));

    const Vehicle* randomCar = test2.find("1234");
    CHECK(!strcmp((*randomCar).getRegistration(), car.getRegistration()));
    
    test2.erase("1234");
    CHECK(test2.size() == 1);

    CHECK(!test2.empty());

}