// #define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../../ObjectHolders/PersonHolder/PersonHolder.h"

SCENARIO("Testing getting person by ID", "[getters]") {
    GIVEN("A holder and a person in it") {
        std::string testPersonName = "test owner's name";
        unsigned int testPersonID = 1;
        Person testPerson(testPersonName, testPersonID);

        PersonHolder pH;
        pH.add(testPerson);

        WHEN("An ID, which belongs to a person in the holder, is searched") {
            Person* resultPerson = pH.getByID(testPersonID);
            THEN("The returned person has the same name and id") {
                REQUIRE(resultPerson->getName() == testPersonName);
                REQUIRE(resultPerson->getID() == testPersonID);
            }
        }

        WHEN("An ID, which does not belong to a person in the holder, is searched") {
            unsigned int wrongID = 2;
            THEN("An exception is thrown") {
                REQUIRE_THROWS_AS(pH.getByID(wrongID), PersonException);
            }
        }
    }
}

SCENARIO("Testing getting all people", "[getters]") {
    GIVEN("A holder and a person in it") {
        std::string testPersonName = "test owner's name";
        unsigned int testPersonID = 1;
        Person testPerson(testPersonName, testPersonID);

        PersonHolder pH;
        pH.add(testPerson);

        WHEN("A getter for all people is called") {
            std::vector<Person> resultPeople = pH.getAllPeople();
            THEN("The returned vector is right") {
                REQUIRE(resultPeople.size() == 1);
                REQUIRE(resultPeople.at(0).getID() == testPersonID);
            }
        }
    }
}

SCENARIO("Testing adding people", "[add]") {
    GIVEN("A holder and a person, who is not in the holder") {
        std::string testPersonName = "test owner's name";
        unsigned int testPersonID = 1;
        Person testPerson(testPersonName, testPersonID);

        PersonHolder pH;

        WHEN("The person is added") {
            pH.add(testPerson);
            THEN("The person can be found in the holder") {
                std::vector<Person> resultPeople = pH.getAllPeople();

                REQUIRE(resultPeople.size() == 1);
                REQUIRE(resultPeople.at(0).getID() == testPersonID);
            }

            AND_WHEN("The same person is added again") {
                THEN("An exception is thrown") {
                    REQUIRE_THROWS_AS(pH.add(testPerson), PersonException);
                }
            }
        }
    }
}

SCENARIO("Testing removing people by ID", "[remove]") {
    GIVEN("A holder and two people, one of whom is in the holder") {
        std::string testPersonNameA = "test owner's name A";
        unsigned int testPersonIDA = 1;
        Person testPersonA(testPersonNameA, testPersonIDA);

        PersonHolder pH;
        pH.add(testPersonA);

        std::string testPersonNameB = "test owner's name B";
        unsigned int testPersonIDB = 2;
        Person testPersonB(testPersonNameB, testPersonIDB);

        WHEN("The person in the holder is released") {
            pH.removeByID(testPersonIDA);
            THEN("The person cannot be found in the holder and the vector's size has changed") {
                std::vector<Person> resultPeople = pH.getAllPeople();

                REQUIRE(resultPeople.size() == 0);

                REQUIRE_THROWS_AS(pH.getByID(testPersonIDA), PersonException);
            }
        }

        WHEN("The person who is not in the holder is removed") {
            THEN("An exceprion is thrown") {
                REQUIRE_THROWS_AS(pH.removeByID(testPersonIDB), PersonException);
            }
        }
    }
}

SCENARIO("Testing getting pointer (operator*) to person Holder", "[operator]") {
    GIVEN("A holder and a person in it") {
        std::string testPersonName = "test owner's name";
        unsigned int testPersonID = 1;
        Person testPerson(testPersonName, testPersonID);

        PersonHolder pH;
        pH.add(testPerson);

        WHEN("A function as called through a pointer to the holder") {
            Person* resultPerson = (*pH)->getByID(testPersonID);
            THEN("The returned result is valid") {
                REQUIRE(resultPerson->getName() == testPersonName);
                REQUIRE(resultPerson->getID() == testPersonID);
            }
        }
    }
}
