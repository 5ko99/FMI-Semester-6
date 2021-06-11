#pragma once

#include "catch2h.h"
#include "../Homework2/Link.cpp"
#include "../Homework2/Base.cpp"


TEST_CASE("Case Link","[Link]"){
    Registration r1("CA2815XA");
    Registration r2("FF0321CC");
    Person p("Ivan",1234);
    Person p0;
    Vehicle v1(r1,"mazda",p0);
    Vehicle v2(r2,"audi",p);
    Link l(v2,p);

    SECTION("Link(Vehicle* veh,Person* p)"){

    }

    SECTION("getVehLink()"){
        REQUIRE(l.getVehLink().getDescr()==v2.getDescr());
    }

    SECTION("getPerLink()"){
        REQUIRE(l.getPerLink().getId()==p.getId());
    }


}

TEST_CASE("Case Base","[Base]"){

    Registration r1("AB1234MN"),r2("CX9153MM"),r3("H0101BV"),r4("Q9072OP"),r5("KI3475ZY");
    Person p0;Person p1("Dragan",101),p2("Petkan",102),p3("Mitkan",103);
    Vehicle v1(r1,"",p0),v2(r2,"",p1),v3(r3,"",p2),v4(r4,"",p3),v5(r5,"",p3);
    Link l1(v2,p1),l2(v3,p2),l3(v4,p3),l4(v5,p3);


    SECTION(""){

    }

    SECTION(""){

    }
    SECTION("existReg(Registration r)"){

    }

    SECTION("existVeh(Vehicle v)"){

    }

    SECTION("existVeh(Vehicle v)"){

    }

    SECTION("VEHICLE (Registration reg,std::string descr)"){

    }

    SECTION("PERSON (std::string name, unsigned int id)"){

    }

    SECTION("ACQUIRE (unsigned id, Registration reg)"){

    }

    SECTION("RELEASE (unsigned id, Registration reg)"){

    }

    SECTION("REMOVE_PER (std::string)"){

    }

    SECTION("REMOVE_PER (std::string)"){

    }

    SECTION("SAVE (std::string)"){

    }

    SECTION("SHOW_PER ()"){

    }

    SECTION("SHOW_VEH ()"){

    }

    SECTION("SHOW_VEH ()"){

    }



}
