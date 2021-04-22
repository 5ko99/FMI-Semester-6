#pragma once

#include "catch2.hpp"
#include "../MyStringGarageVihicle/MyString.cpp"

TEST_CASE("Case MyString","[MyString]"){

    SECTION("MyString()"){

    MyString a;
    REQUIRE(a.size()==0);
    MyString b("");
    REQUIRE(a.c_str()==b.c_str());

    }

    SECTION("MyString(const MyString& str)"){

    MyString b("Chushka");
    REQUIRE(b.size()==7);

    }
    SECTION("MyString& operator=(const MyString& str)"){

        MyString a("bjj");
        MyString b;
        b=a;
        REQUIRE(b.size()==3);


    }

    SECTION("~MyString()"){



    }
    SECTION("MyString(const char* str)"){

        MyString a("mkoo");
        REQUIRE(a.size()==4);
        REQUIRE(strcmp(a.c_str(),"mkoo"));

    }

    SECTION("char& at(std::size_t pos)"){

    MyString a("qwertyuio");
    REQUIRE(a.at(1)=='q');
    REQUIRE(a.at(2)=='w');
    REQUIRE(a.at(3)=='e');
    REQUIRE(a.at(4)=='r');
    REQUIRE(a.at(5)=='t');
    REQUIRE(a.at(6)=='y');
    REQUIRE(a.at(7)=='u');
    //REQUIRE_THROWS(a.at(0)=='q');
    REQUIRE_THROWS(a.at(17)=='q');

    }
    SECTION("const char& at(std::size_t pos) const"){

    const MyString a("qwertyuio");
    REQUIRE(a.at(1)=='q');
    REQUIRE(a.at(2)=='w');
    REQUIRE(a.at(3)=='e');
    REQUIRE(a.at(4)=='r');
    REQUIRE(a.at(5)=='t');
    REQUIRE(a.at(6)=='y');
    REQUIRE(a.at(7)=='u');
    //REQUIRE_THROWS(a.at(0)=='q');
    //REQUIRE_THROWS(a.at(17)=='q');
    }

    SECTION("char& operator[](std::size_t pos)"){

    MyString a("qwertyuio");
    REQUIRE(a[1]=='q');
    REQUIRE(a[2]=='w');
    REQUIRE(a[3]=='e');
    REQUIRE(a[4]=='r');
    REQUIRE(a[5]=='t');
    REQUIRE(a[6]=='y');
    REQUIRE(a[7]=='u');
    //REQUIRE_THROWS(a[0]=='q');

    }

    SECTION("const char& operator[](std::size_t pos) const"){

    const MyString a("qwertyuio");
    REQUIRE(a[1]=='q');
    REQUIRE(a[2]=='w');
    REQUIRE(a[3]=='e');
    REQUIRE(a[4]=='r');
    REQUIRE(a[5]=='t');
    REQUIRE(a[6]=='y');
    REQUIRE(a[7]=='u');
    //REQUIRE_THROWS(a[0]=='q');

    }

    SECTION("char& front() "){

    MyString a("12kn3"),b("fnjvfnv");
    REQUIRE(a.front()=='1');
    REQUIRE(a.front()!='3');
    REQUIRE(b.front()=='f');
    REQUIRE(b.front()!='v');

    }
    SECTION("char& back()"){

    MyString a("12kn3"),b("fnjvfnv");
    REQUIRE(a.back()!='1');
    REQUIRE(a.back()=='3');
    REQUIRE(b.back()!='f');
    REQUIRE(b.back()=='v');

    }

    SECTION("const char& back() const "){

    const MyString a("12kn3"),b("fnjvfnv");
    REQUIRE(a.back()!='1');
    REQUIRE(a.back()=='3');
    REQUIRE(b.back()!='f');
    REQUIRE(b.back()=='v');

    }
    SECTION("bool empty() const "){

        MyString a(""),b("fnj");
        REQUIRE(a.empty()==true);
        REQUIRE(b.empty()==false);

    }

    SECTION("std::size_t size() const "){

        MyString a("1"),b("fnjvfnv"),c("");
        REQUIRE(a.size()==1);
        REQUIRE(b.size()==7);
        REQUIRE(c.size()==0);
    }

    SECTION("void clear()"){

        MyString b("fnjvfnv");
        b.clear();
        REQUIRE(b.size()==0);
    }


    SECTION("MyString& operator+=(char c)"){

        MyString b("fnjvfnv");
        b+='c';
        REQUIRE(b.size()==8);
        REQUIRE(strcmp(b.c_str(),"fnjvfnvc"));

    }

    SECTION("MyString& operator+=(const MyString& rhs)"){

        MyString b("fnjvfnv"),a("hbf2,");
        b+=a;
        REQUIRE(b.size()==12);
        REQUIRE(strcmp(b.c_str(),"fnjvfnvchbf2,"));

    }

    SECTION("MyString operator+(char c) const"){

        MyString b("fnjvfnv"),a("hbf2,"),c;
        c=a+b;
        REQUIRE(c.size()==12);
        REQUIRE(strcmp(c.c_str(),"hbf2,fnjvfnv"));

    }

//    SECTION("MyString operator+(const MyString& rhs) const "){
//
//        const MyString b("fnjvfnv"),a("hbf2,"),c;
//        c=a+b;
//        REQUIRE(c.size()==12);
//        REQUIRE(strcmp(c.c_str(),"hbf2,fnjvfnv"));
//
//    }

    SECTION("const char* c_str() const"){

        const MyString b("fnjvfnv"),a("1234"),c;
        REQUIRE(strcmp(b.c_str(),"fnjvfnv"));
        REQUIRE(strcmp(a.c_str(),"1234"));
        REQUIRE(strcmp(c.c_str(),""));

    }

    SECTION("bool operator==(const MyString &rhs) const"){

        MyString b("rty");
        REQUIRE(strcmp(b.c_str(),"rty"));
        REQUIRE(b.c_str()=="rty");

    }

    SECTION("bool operator<(const MyString &rhs) const"){

        MyString b("abc"),c("cde");
        REQUIRE(!(strcmp(c.c_str(),"rty")));
        REQUIRE(c.c_str()<b.c_str());

    }




}
