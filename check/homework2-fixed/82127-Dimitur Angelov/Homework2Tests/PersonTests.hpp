#pragma once

#include "catch2h.h"
#include "../Homework2/Person.cpp"


TEST_CASE("Case Person","[Person]"){

    SECTION("Person(const std::string name,unsigned int id)"){
        REQUIRE_THROWS(Person ("iuhsdb43",1234));
        REQUIRE_THROWS(Person ("Stefan Hisarov",-12));//will not throw because -12 in unsigned int is 4294967284 and a valid id
        REQUIRE_THROWS(Person ("Agent",007));//will not throw because 007 in unsigned int is 7 and a valid id. Will not remember the leading zeros
        REQUIRE_THROWS(Person ("ko'q8rqev",124));
        REQUIRE_THROWS(Person ("apv89ver",-9));
        REQUIRE_NOTHROW(Person ("Ivan Ivanov",1217));
        REQUIRE_NOTHROW(Person ("Michael Schumacher",82));
        REQUIRE_NOTHROW(Person ("Pesho",1));
        REQUIRE_NOTHROW(Person ("Dimitar Angelov",123456789));
    }

    SECTION("std::string& getName()"){
        Person a("Ivan Ivanov",1217);
        Person b("Pesho",1);
        Person c("Mag Stavri",0);
        Person d("Michael Schumacher",82);
        Person e("Dimitar Angelov",123456789);
        REQUIRE(a.getName()=="Ivan Ivanov");
        REQUIRE(b.getName()=="Pesho");
        REQUIRE(c.getName()=="Mag Stavri");
        REQUIRE(d.getName()=="Michael Schumacher");
        REQUIRE(e.getName()=="Dimitar Angelov");
    }

    SECTION("unsigned int& getId()"){
        Person a("Ivan Ivanov",1217);
        Person b("Pesho",1);
        Person c("Mag Stavri",0);
        Person d("Michael Schumacher",82);
        Person e("Dimitar Angelov",123456789);
        REQUIRE(a.getId()==1217);
        REQUIRE(b.getId()==1);
        REQUIRE(c.getId()==0);
        REQUIRE(d.getId()==82);
        REQUIRE(e.getId()==123456789);
    }





}
