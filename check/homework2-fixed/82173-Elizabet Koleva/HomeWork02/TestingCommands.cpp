#include "Catch2/catch_amalgamated.hpp"
#include "Commands.h"

TEST_CASE("Testing class Commands", "[commands]")
{
    SECTION("Testing static functions")
    {
        GIVEN("Vectors")
        {
            std::vector<Vehicle*> allVehicles;
            std::vector<Person*> people;

            WHEN("Testing get car position")
            {
                Vehicle* test1 = new Vehicle(Registration("AA1234BB"), "Test");
                Vehicle* test2 = new Vehicle(Registration("BA1234BB"), "Test");

                allVehicles.push_back(test1);
                allVehicles.push_back(test2);

                REQUIRE(Commands::getCarPosition("AA1234BB", allVehicles) == 0);
                REQUIRE(Commands::getCarPosition("BA1234BB", allVehicles) == 1);
            
                allVehicles.clear();
                allVehicles.resize(0);
                delete test1;
                delete test2;
            }
        
            WHEN("Testing get person position")
            {
                Person* test1 = new Person("Test", 123);
                Person* test2 = new Person("Test", 333);

                people.push_back(test1);
                people.push_back(test2);

                THEN("Testing static") 
                {
                    REQUIRE(Commands::personPosition(123, people) == 0);
                    REQUIRE(Commands::personPosition(333, people) == 1);
                }
            
                delete test1;
                delete test2;
                people.clear();
                people.resize(0);
            }
        }
    }
        

    SECTION("Testing main functions")
    {
        GIVEN("Vectors and object")
        {
            std::vector<Vehicle*> allVehicles;
            std::vector<Person*> people;
            Commands test;

            WHEN("Testing add car")
            {
                test = "Vehicle AA1234EE Test car";
                THEN("Testing the functions")
                {
                    REQUIRE_NOTHROW(test.addCar(8, 17, allVehicles));
                    REQUIRE(Commands::getCarPosition("AA1234EE", allVehicles) == 0);

                    test = "Vehicle AA1234EE Test car";
                    test.addCar(8, 17, allVehicles);
                    REQUIRE(Commands::getCarPosition("AA1234EE", allVehicles) == 0);
                }
                
                // REQUIRE_THROWS_AS(test.addCar(8, 17, allVehicles), std::invalid_argument);
            }
        
            WHEN("Testing add person")
            {
                test = "Person Ivan 123";
                REQUIRE_NOTHROW(test.addPerson(7, 0, 12, people));
                
                test = "Person Ivan 123";
                REQUIRE_THROWS_AS(test.addPerson(7, 0, 12, people), std::invalid_argument);
                REQUIRE(Commands::personPosition(123, people) == 0);
            

                test = "Person \"Chris Yankov\" 333";
                REQUIRE_NOTHROW(test.addPerson(8, 20, 22, people));

                test = "Person \"Chris Yankov\" 333";
                REQUIRE_THROWS_AS(test.addPerson(8, 20, 22, people), std::invalid_argument);
                REQUIRE(Commands::personPosition(333, people) == 1);
                
            }

            WHEN("Testing acquire car")
            {
                test = "Vehicle AA1234EE Test car";
                REQUIRE_NOTHROW(test.addCar(8, 17, allVehicles));
                test = "Person Ivan 123";
                REQUIRE_NOTHROW(test.addPerson(7, 0, 12, people));

                test = "Acquire 123 AA1234EE";
                REQUIRE_NOTHROW(test.acquireCar(8, 12, people, allVehicles));

                REQUIRE((*allVehicles[0]).getOwner() == (people[0]));
            }

            WHEN("Testing release car")
            {            
                test = "Vehicle AA1234EE Test car";
                REQUIRE_NOTHROW(test.addCar(8, 17, allVehicles));
                test = "Person Ivan 123";
                REQUIRE_NOTHROW(test.addPerson(7, 0, 12, people));
                test = "Acquire 123 AA1234EE";
                REQUIRE_NOTHROW(test.acquireCar(8, 12, people, allVehicles));

                REQUIRE((*allVehicles[0]).getOwner() == (people[0]));

                // test = "Release 123 AA1234EE";
                // REQUIRE_NOTHROW(test.releaseCar(8, 12, people, allVehicles));
                
                // REQUIRE(((*allVehicles[0]).getOwner() == (*people[0])) == false);
            }

            WHEN("Testing remove object")
            {
                test = "Vehicle AA1234EE Test car";
                REQUIRE_NOTHROW(test.addCar(8, 17, allVehicles));
                test = "Remove AA1234EE";
                REQUIRE_NOTHROW(test.removeObject(7, people, allVehicles));
                test = "Remove AA1234EE";
                REQUIRE_THROWS_AS(test.removeObject(7, people, allVehicles), std::invalid_argument);

                test = "Remove 123";
                test = "Person Ivan 123";
                REQUIRE_NOTHROW(test.addPerson(0, 0, 12, people));
                //test.removeObject(7, people, allVehicles);
                REQUIRE_NOTHROW(test.removeObject(0, people, allVehicles));
                test = "Remove 123";
                REQUIRE_THROWS_AS(test.removeObject(0, people, allVehicles), std::invalid_argument);

                test = "Remove probaGreshkaProba";
                REQUIRE_THROWS_AS(test.removeObject(7, people, allVehicles), std::invalid_argument);

                // test = "Remove 123";
                // test = "Person Ivan 123";
                // REQUIRE_NOTHROW(test.addPerson(7, 0, 12, people));
                // REQUIRE_NOTHROW(test.removeObject(7, people, allVehicles));
                // test = "Remove 123";
                // REQUIRE_THROWS_AS(test.removeObject(7, people, allVehicles), std::invalid_argument);

                // test = "Remove probaGreshkaProba";
                // REQUIRE_THROWS_AS(test.removeObject(7, people, allVehicles), std::invalid_argument);

            }
        }
    }

    SECTION("Testing operator =")
    {
        GIVEN("Object and string")
        {
            Commands testCommand;   
            string userCommand = "Ok";

            WHEN("Assigning user's input")
            {
                // testCommand = userCommand;
                REQUIRE_NOTHROW(testCommand = userCommand);
                REQUIRE(testCommand.getCommand() == "Ok");

                REQUIRE_NOTHROW(testCommand = "Yasno");
                REQUIRE(testCommand.getCommand() == "Yasno");
            }
        }
    }
}
