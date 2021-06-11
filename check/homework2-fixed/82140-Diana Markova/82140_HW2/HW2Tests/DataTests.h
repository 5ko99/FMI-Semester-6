#ifndef DATATESTS_H
#define DATATESTS_H
#include "../HW2/Data.h"
#include "catch2.hpp"
#include <cstddef>
#include <string>
#include <fstream>

Data& dataBase = Data::getInstance();
TEST_CASE("Data can store different vehicles and people", "[Data]")
{
    char name[20]="some name";
    char descrpt[20]="some descrpt";
    char reg[]="AA0000AA";
    char modReg[20];
    std::strcpy(modReg, reg);
    for(std::size_t i=0; i<100; ++i)
    {
        REQUIRE_NOTHROW(dataBase.newPerson(name, i));
    }
    for(std::size_t i=0; i<100; ++i)
    {
        REQUIRE_THROWS(dataBase.newPerson(name, i));
    }
    for(std::size_t i=0; i<=25; ++i)
    {
        modReg[0]+=i;
        REQUIRE_NOTHROW(dataBase.newVehicle(modReg, descrpt));
        modReg[0]='A';
    }
    for(std::size_t i=0; i<=25; ++i)
    {
        modReg[1]+=i;
        modReg[7]='B';
        REQUIRE_NOTHROW(dataBase.newVehicle(modReg, descrpt));
        modReg[7]='A';
        modReg[1]='A';
    }
    for(std::size_t i=0; i<=25; ++i)
    {
        modReg[0]+=i;
        REQUIRE_THROWS(dataBase.newVehicle(modReg, descrpt));
        modReg[0]='A';
    }
}

TEST_CASE("Acquire works properly", "[Data]")
{
    char reg[]="AA0000AA";
    char modReg[20];
    std::strcpy(modReg, reg);
    for(std::size_t i=0; i<=25; ++i)
    {
        modReg[0]+=i;
        REQUIRE_NOTHROW(dataBase.acquire(std::to_string(i).c_str(), modReg));
        modReg[0]='A';
    }
    for(std::size_t i=0; i<=25; ++i)
    {
        modReg[0]+=i;
        REQUIRE_NOTHROW(dataBase.acquire(std::to_string(i).c_str(), modReg));
        modReg[0]='A';
    }
    for(std::size_t i=0; i<=25; ++i)
    {
        modReg[1]+=i;
        modReg[7]='B';
        //std::cout<<modReg<<std::endl;
        REQUIRE_NOTHROW(dataBase.acquire(std::to_string(i).c_str(), modReg));
        modReg[7]='A';
        modReg[1]='A';
    }
    REQUIRE_THROWS(dataBase.acquire(std::to_string(101).c_str(), modReg));
    REQUIRE_THROWS(dataBase.acquire(std::to_string(25).c_str(), "CA2525N0"));
    std::ofstream oFile("longList.txt");
    if(oFile) dataBase.save(oFile);
}
TEST_CASE("Release works properly", "[Data]")
{
    char reg[]="AA0000AA";
    char modReg[20];
    std::strcpy(modReg, reg);
    for(std::size_t i=0; i<=25; ++i)
    {
        modReg[1]+=i;
        modReg[7]='B';
        //std::cout<<modReg<<std::endl;
        REQUIRE_NOTHROW(dataBase.release(std::to_string(i).c_str(), modReg));
        modReg[7]='A';
        modReg[1]='A';
    }
    REQUIRE_THROWS(dataBase.release(std::to_string(101).c_str(), modReg));
    REQUIRE_THROWS(dataBase.release(std::to_string(25).c_str(), "CA2525N0"));
}


#endif // DATATESTS_H
