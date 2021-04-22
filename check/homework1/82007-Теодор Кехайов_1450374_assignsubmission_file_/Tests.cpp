#include <iostream>
#include "../MyString.h"
#include "../Vehicle.h"
#include "../Garage.h"


bool testError = false;
using TestFunction = void(*)();

bool runTest(TestFunction pfn , const char* name)
{
    testError = true;
    std::cout<<"Running test:"<<name<<"...";
    pfn();
    std::cout<<(testError ? "OK\n" : "FAILED");

    return testError;
}

int main()
{
}


#define TEST_CASE(name)                    \
void name();                               \
bool test_##name=runTest(name,#name);      \
void name()


#define CHECK(condition) testError = (condition)

///-----------------------------------------------

/// TESTING functions of class MyString

TEST_CASE(test_MyString_funcAt)
{
    MyString a("testing");
    CHECK(a.at(0)=='t');
    CHECK(a.at(4)=='i');
    CHECK(a.at(6)=='g');
}

TEST_CASE(test_MyString_funcFront)
{
    MyString a("testing");
    CHECK(a.front()=='t');
}

TEST_CASE(test_MyString_funcBack)
{
    MyString a("testing");
    CHECK(a.back()=='g');
}

TEST_CASE(test_MyString_funcEmpty)
{
    MyString a("testing"),b;
    CHECK(!a.empty());
    CHECK(b.empty());
}

TEST_CASE(test_MyString_funcSize)
{
    MyString a("testing"),b;
    CHECK(a.size()==7);
    CHECK(b.size()==0);
}

TEST_CASE(test_MyString_funcClear)
{
    MyString a("testing"),b;
    a.clear();
    b.clear();
    CHECK(a.size()==0);
    CHECK(b.size()==0);
}

TEST_CASE(test_MyString_func_C_Str)
{
    MyString a("testing");
    CHECK(strcmp(a.c_str(),"testing")==0);
}

TEST_CASE(test_MyString_funcPushBack)
{
    MyString a("testing");
    char b='!';
    a.push_back(b);
    a.push_back('1');
    CHECK(a==MyString("testing!1"));
}

TEST_CASE(test_MyString_funcPopBack)
{
    MyString a("testing");
    a.pop_back();
    CHECK(a.size()==6);
    CHECK(a==MyString("testin"));
}

TEST_CASE(test_MyString_operatorEven)
{
    MyString a,b;
    a=MyString("first");
    b=MyString("second");
    a=b;
    CHECK(a=="second");
    CHECK(b=="second");
}

TEST_CASE(test_MyString_operatorForPosition)
{
    MyString a("testing");
    CHECK(a[0]=='t');
    CHECK(a[4]=='i');
    CHECK(a[6]=='g');
}

TEST_CASE(test_MyString_operatorPlusEven)
{
    MyString a("testing"),b("!");
    b+='!';
    a+='!';
    a+=b;
    CHECK(a==MyString("testing!!!"));
}

TEST_CASE(test_MyString_operatorPlus)
{
    MyString a("testing"),b(" ");
    MyString c = a+b;
    MyString d = c+"is good";
    CHECK(c==MyString("testing "));
    CHECK(d==MyString("testing is good"));
}

TEST_CASE(test_MyString_operatorEvenEven)
{
    MyString a("testing");
    MyString b=a;

    CHECK(a==b);
    CHECK(MyString("one")=="one");
}

TEST_CASE(test_MyString_operatorBigger)
{
    MyString a("testing"),b("Ace");
    CHECK(strcmp(a.c_str(),b.c_str())>0);
}


/// TESTING class Vehicle

TEST_CASE(test_Vehicle_functions)
{
    Vehicle car("A 8432 KF","red bmw",1);
    CHECK(strcmp(car.registration(),"A 8432 KF")==0);
    CHECK(strcmp(car.description(),"red bmw")==0);
    CHECK(car.space()==1);
}

/// TESTING

TEST_CASE(test_Garage_funcSize)
{
    Vehicle t1("123","456",1);
    Vehicle t2("hello","world",2);
    Garage test(3);

    test.insert(t1);
    test.insert(t2);

    CHECK(test.size()==2);
}

TEST_CASE(test_Garage_funcInsert)
{
    Garage test(3);
    Vehicle t1("123","456",3);
    test.insert(t1);

    CHECK(test.size()==1);
}

TEST_CASE(test_Garage_operatorEven)
{
    Garage test(3);
    Vehicle t1("123","456",3);
    test.insert(t1);
    Garage b=test;
    CHECK(b.size()==1);
}

TEST_CASE(test_Garage_operatorForPosition)
{
    Garage test(5);
    Vehicle t1("123","456",3);
    Vehicle t2("hello","world",2);
    test.insert(t1);
    test.insert(t2);
    CHECK(test[0].registration()==t1.registration());
    CHECK(test[0].description()==t1.description());
    CHECK(test[0].space()==t1.space());
    CHECK(test[1].registration()==t2.registration());
    CHECK(test[1].description()==t2.description());
    CHECK(test[1].space()==t2.space());
}

TEST_CASE(test_Garage_funcAt)
{
    Garage test(5);
    Vehicle t1("123","456",3);
    Vehicle t2("hello","world",2);
    test.insert(t1);
    test.insert(t2);
    CHECK(test.at(0).registration()==t1.registration());
    CHECK(test.at(0).description()==t1.description());
    CHECK(test.at(0).space()==t1.space());
    CHECK(test.at(1).registration()==t2.registration());
    CHECK(test.at(1).description()==t2.description());
    CHECK(test.at(1).space()==t2.space());
}

TEST_CASE(test_Garage_funcEmpty)
{
    Garage test(1);
    CHECK(test.empty());
}

TEST_CASE(test_Garage_funcErase)
{
    Garage test(5);
    Vehicle t1("123","456",3);
    Vehicle t2("hello","world",2);
    test.insert(t1);
    test.insert(t2);

    test.erase("123");
    CHECK(test.size()==1);

    test.erase("hello");
    CHECK(test.empty());
}

TEST_CASE(test_Garage_funcClear)
{
    Garage test(5);
    Vehicle t1("123","456",3);
    Vehicle t2("hello","world",2);
    test.insert(t1);
    test.insert(t2);

    test.clear();
    CHECK(test.empty());
}

TEST_CASE(test_Garage_funcFind)
{
    Garage test(5);
    Vehicle t1("123","456",3);
    Vehicle t2("hello","world",2);
    test.insert(t1);
    test.insert(t2);

    CHECK(test.find("123")->registration()==t1.registration());
    CHECK(test.find("hello")->space()==2);
}
