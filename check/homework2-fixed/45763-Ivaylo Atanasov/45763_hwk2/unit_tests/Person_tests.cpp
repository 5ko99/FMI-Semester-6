#include "../Homework_2_2/Vehicle/Vehicle.hpp"
#include "catch2.hpp"

TEST_CASE("constructor"){
    SECTION("correct input"){
        bool isSafe = true;
        try{
            std::string name = "ivan ivanov";
            unsigned int uid = 15;
            Person p(name, uid);
            REQUIRE(p.getName() == name);
            REQUIRE(p.getUid() == uid);
        } catch(const std::exception& e){
            isSafe = false;
        }
        REQUIRE(isSafe);
    }
}

TEST_CASE("ownership functions"){
    
    SECTION("acquire single vehicle / owns() function"){
        Person p1("ivan", 11);
        Vehicle v1("AB1111CD", "desc1");
        REQUIRE(!p1.owns(v1.getReg()));
        p1.acquire(v1);
        REQUIRE(p1.owns(v1.getReg()));
        REQUIRE(v1.getOwner().getUid() == p1.getUid());
    }
    
    SECTION("acquire multiple / releaseAll"){
        Person p1("ivan", 11);
        Vehicle v1("AB1111CD", "desc1");
        Vehicle v2("AB2222CD", "desc2");
        Vehicle v3("AB3333CD", "desc3");
        
        p1.acquire(v1);
        REQUIRE(p1.owns(v1.getReg()));
        REQUIRE(v1.getOwner().getUid() == p1.getUid());
        
        p1.acquire(v2);
        REQUIRE(p1.owns(v2.getReg()));
        REQUIRE(v2.getOwner().getUid() == p1.getUid());
        
        p1.acquire(v3);
        REQUIRE(p1.owns(v3.getReg()));
        REQUIRE(v3.getOwner().getUid() == p1.getUid());
        
        p1.releaseAll();
        REQUIRE(!p1.owns(v1.getReg()));
        REQUIRE(!p1.owns(v2.getReg()));
        REQUIRE(!p1.owns(v3.getReg()));
    }
    
    SECTION("call acquire on an already owned vehicle"){
        Person p1("ivan", 11);
        Person p2("dragan", 22);
        Vehicle v1("AB1111CD", "desc1");
        
        p1.acquire(v1);
        REQUIRE(p1.owns(v1.getReg()));
        p2.acquire(v1);
        REQUIRE(!p1.owns(v1.getReg()));
        REQUIRE(p2.owns(v1.getReg()));
    }
    
    SECTION("release"){
        Person p1("ivan", 11);
        Vehicle v1("AB1111CD", "desc1");
        
        p1.acquire(v1);
        REQUIRE(p1.owns(v1.getReg()));
        p1.release(v1.getReg());
        REQUIRE(!p1.owns(v1.getReg()));
    }
    
    SECTION("release a non owned vehicle"){
        Person p1("ivan", 11);
        Person p2("dragan", 22);
        Vehicle v1("AB1111CD", "desc1");
        
        p1.acquire(v1);
        REQUIRE(p1.owns(v1.getReg()));
        
        bool isSafe = false;
        try{
            p2.release(v1.getReg());
        } catch(const std::exception& e){
            isSafe = true;
        }
        REQUIRE(isSafe);
    }
    
}
