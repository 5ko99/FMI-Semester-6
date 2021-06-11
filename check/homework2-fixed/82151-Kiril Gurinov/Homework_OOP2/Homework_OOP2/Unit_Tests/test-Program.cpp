#include "catch_amalgamated.hpp"
#include "Program.h"

TEST_CASE("Program tests")
{
    Program program;
    REQUIRE_FALSE(program.isRunning());

    program.getInput("PERSON \"Steven Wolfe\" 1");
    program.getInput("Vehicle XY1111YX idunno");
    program.getInput("acquire 1 XY111YX");

    REQUIRE_THROWS_AS(program.addPerson("Adlof", 1), std::exception);
    REQUIRE_THROWS_AS(program.addVehicle("XY1111YX", "hehe"), std::exception);

    REQUIRE_THROWS_AS(program.addVehicleOwner(2, "XY1111YX"), std::exception);
    REQUIRE_THROWS_AS(program.addVehicleOwner(1, "X1111YX"), std::exception);

    REQUIRE_THROWS_AS(program.releaseVehicle(2, "XY1111YX"), std::exception);
    REQUIRE_THROWS_AS(program.releaseVehicle(1, "X1111YX"), std::exception);
    

    REQUIRE_THROWS_AS(program.remove("X1111YX"), std::exception);
    REQUIRE_THROWS_AS(program.remove("2"), std::exception);
    REQUIRE_THROWS_AS(program.remove("-1"), std::exception);
    REQUIRE_THROWS_AS(program.remove("C11d"), std::exception);

    REQUIRE_THROWS_AS(program.show("3"), std::exception);
    REQUIRE_THROWS_AS(program.show("X1111YX"), std::exception);
    REQUIRE_THROWS_AS(program.show("1jk5h1uih78"), std::exception);
}
