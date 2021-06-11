#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Commands.h"
#include "Container.h"

TEST_CASE("Add vehicle or person")
{
    Container storage;
    {
        Command cmd("VEHICLE CA1234CA \"CAR 1\"");
        REQUIRE_NOTHROW(cmd.execute(storage));
    }
    {
        Command cmd(("VEHICLE CA1234CA \"CAR 1\""));
        REQUIRE_THROWS_AS(cmd.execute(storage), std::invalid_argument);
    }
    {
        Command cmd(("VEHICLE Ca1234CA \"CAR 1\""));
        REQUIRE_THROWS_AS(cmd.execute(storage), std::invalid_argument);
    }
    {
        Command cmd(R"(PeRsOn "Vlado Iliev" 123)");
        REQUIRE_NOTHROW(cmd.execute(storage));
    }
    {
        Command cmd(R"(PeRsOn "Vlado Iliev" 1c3)");
        REQUIRE_THROWS_AS(cmd.execute(storage), std::invalid_argument);
    }
    {
        Command cmd(R"(PeRsOn "Vlado Iliev" 123)");
        REQUIRE_THROWS_AS(cmd.execute(storage), std::invalid_argument);
    }
    {
        Command cmd(R"(save "..\Commands And Container\Tests\test_info.txt")");
        cmd.execute(storage);
    }
}

TEST_CASE("ACQUIRE and RELEASE")
{
    Container storage;
    storage.loadFromFile(R"(..\Commands And Container\Tests\test_info.txt)");

    {
        Command cmd(R"(ACQUIRE 123 CA1234CA)");
        REQUIRE_NOTHROW(cmd.execute(storage));
    }
    {
        Command cmd(R"(ACQUIRE 123 CA1234CA)");
        REQUIRE_THROWS_AS(cmd.execute(storage), std::invalid_argument);
    }
    {
        Command cmd(R"(RELEASE 123 CA1234CA)");
        REQUIRE_NOTHROW(cmd.execute(storage));
    }
    {
        Command cmd(R"(RELEASE 123 CA1234CA)");
        REQUIRE_THROWS_AS(cmd.execute(storage), std::invalid_argument);
    }
}

TEST_CASE("REMOVE")
{
    Container storage;
    storage.loadFromFile(R"(..\Commands And Container\Tests\test_info.txt)");
    {
        Command cmd(R"(REMOVE 123)");
        REQUIRE_NOTHROW(cmd.execute(storage));
    }
    {
        Command cmd(R"(REMOVE 123)");
        REQUIRE_THROWS_AS(cmd.execute(storage), std::invalid_argument);
    }
    {
        Command cmd(R"(REMOVE 456)");
        REQUIRE_THROWS_AS(cmd.execute(storage), std::invalid_argument);
    }
    {
        Command cmd(R"(REMOVE CA1234CA)");
        REQUIRE_NOTHROW(cmd.execute(storage));
    }
    {
        Command cmd(R"(REMOVE CA1234CA)");
        REQUIRE_THROWS_AS(cmd.execute(storage), std::invalid_argument);
    }
    {
        Command cmd(R"(REMOVE CA4567CA)");
        REQUIRE_THROWS_AS(cmd.execute(storage), std::invalid_argument);
    }
}
