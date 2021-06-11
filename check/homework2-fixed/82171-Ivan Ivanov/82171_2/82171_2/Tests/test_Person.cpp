// #define CATCH_CONFIG_MAIN
#include "../Catch2/catch.hpp"
#include "../Vehicle/Vehicle.h"
#include "../Person/Person.h"

SCENARIO("Testing copy constructor of person", "[copy]") {
    GIVEN("A valid person") {
        std::string testPersonNameA = "test owner's name A";
        unsigned int testPersonIDA = 1;
        Person testPersonA(testPersonNameA, testPersonIDA);

        WHEN("Another is created through copy constructor") {
            Person testPersonB(testPersonA);

            THEN("The id and the veС…icles are equal") {
                REQUIRE(testPersonA.getID() == testPersonB.getID());
                REQUIRE(testPersonA.getName() == testPersonB.getName());
                REQUIRE(testPersonA.getVehiclesCount() == testPersonB.getVehiclesCount());
            }
        }
    }
}

SCENARIO("Testing copy assignment of person", "[copy]") {
    GIVEN("Two valid people") {
        std::string testPersonNameA = "test owner's name A";
        unsigned int testPersonIDA = 1;
        Person testPersonA(testPersonNameA, testPersonIDA);

        std::string testPersonNameB = "test owner's name B";
        unsigned int testPersonIDB = 2;
        Person testPersonB(testPersonNameB, testPersonIDB);

        WHEN("Assignment operator is used") {
            testPersonB = testPersonA;

            THEN("The id and the veС…icles are equal") {
                REQUIRE(testPersonA.getID() == testPersonB.getID());
                REQUIRE(testPersonA.getName() == testPersonB.getName());
                REQUIRE(testPersonA.getVehiclesCount() == testPersonB.getVehiclesCount());
            }
        }
    }
}

SCENARIO("Testing getting id", "[getters]") {
    GIVEN("A valid person") {
        std::string testPersonNameA = "test owner's name A";
        unsigned int testPersonIDA = 1;
        Person testPersonA(testPersonNameA, testPersonIDA);

        THEN("The id returned is right") {
            REQUIRE(testPersonA.getID() == testPersonIDA);
        }
    }
}

SCENARIO("Testing getting name", "[getters]") {
    GIVEN("A valid person") {
        std::string testPersonNameA = "test owner's name A";
        unsigned int testPersonIDA = 1;
        Person testPersonA(testPersonNameA, testPersonIDA);

        THEN("The name returned is right") {
            REQUIRE(testPersonA.getName() == testPersonNameA);
        }
    }
}

SCENARIO("Testing getting the person's vehicles and their count", "[getters]") {
    GIVEN("A valid person with no vehicles") {
        std::string testPersonName = "test owner's name";
        unsigned int testPersonID = 1;
        Person testPerson(testPersonName, testPersonID);

        THEN("The number of vehicles returned is 0") {
            REQUIRE(testPerson.getVehiclesCount() == 0);
        }
    }

    GIVEN("A valid person with vehicles") {
        std::string testPersonName = "test owner's name";
        unsigned int testPersonID = 1;
        Person testPerson(testPersonName, testPersonID);

        std::string testRegistrationValueA = "aa0000AA";
        Registration testRegistrationA(testRegistrationValueA);
        std::string testDescriptionValueA = "test description A";
        
        Vehicle testVehicleA(testRegistrationA, testDescriptionValueA);

        std::string testRegistrationValueB = "aa0000BB";
        Registration testRegistrationB(testRegistrationValueB);
        std::string testDescriptionValueB = "test description B";
        
        Vehicle testVehicleB(testRegistrationB, testDescriptionValueB);

        testPerson.addVehicle(*testVehicleA);
        testPerson.addVehicle(*testVehicleB);

        THEN("The vehicles and their number is right ") {
            VehiclePtr* ownedVehicles = testPerson.getVehicles();

            REQUIRE(testPerson.getVehiclesCount() == 2);
            REQUIRE(ownedVehicles[0]->getRegistration() == testRegistrationA);
            REQUIRE(ownedVehicles[1]->getRegistration() == testRegistrationB);

            delete[] ownedVehicles;
        }
    }
}

SCENARIO("Testing adding and removing vehicles", "[ownershipControl]") {
    GIVEN("A valid person, who owns no vehicles, and four vehicles") {
        std::string testPersonName = "test owner's name";
        unsigned int testPersonID = 1;
        Person testPerson(testPersonName, testPersonID);

        std::string testRegistrationValueA = "aa0000AA";
        Registration testRegistrationA(testRegistrationValueA);
        std::string testDescriptionValueA = "test description A";
        
        Vehicle testVehicleA(testRegistrationA, testDescriptionValueA);

        std::string testRegistrationValueB = "aa0000BB";
        Registration testRegistrationB(testRegistrationValueB);
        std::string testDescriptionValueB = "test description B";
        
        Vehicle testVehicleB(testRegistrationB, testDescriptionValueB);

        std::string testRegistrationValueC = "aa0000CC";
        Registration testRegistrationC(testRegistrationValueC);
        std::string testDescriptionValueC = "test description C";
        
        Vehicle testVehicleC(testRegistrationC, testDescriptionValueC);

        std::string testRegistrationValueD = "aa0000DD";
        Registration testRegistrationD(testRegistrationValueD);
        std::string testDescriptionValueD = "test description D";
        
        Vehicle testVehicleD(testRegistrationD, testDescriptionValueD);

        THEN("Expect release function to throw whena vehicle is released ") {
            REQUIRE_THROWS_AS(testPerson.releaseVehicle(*testVehicleA), PersonException);   
        }

        WHEN("A vehicle is added") {
            testPerson.addVehicle(*testVehicleA);
            
            THEN("The vehicle is added and the count of the owned vehicles changes") {
                VehiclePtr* ownedVehicles = testPerson.getVehicles();

                REQUIRE(testPerson.getVehiclesCount() == 1);
                REQUIRE(ownedVehicles[0]->getRegistration() == testRegistrationValueA);

                delete[] ownedVehicles;
            }

            AND_WHEN("An already owned vehicle is added") {
                THEN("An exception is thrown") {
                    REQUIRE_THROWS_AS(testPerson.addVehicle(*testVehicleA), PersonException);
                }
            }

            AND_WHEN("A second and third vehicle are added") {
                testPerson.addVehicle(*testVehicleB);
                testPerson.addVehicle(*testVehicleC);
                
                THEN("The vehicles are added and the count of the owned ones changes") {
                    VehiclePtr* ownedVehicles = testPerson.getVehicles();

                    REQUIRE(testPerson.getVehiclesCount() == 3);
                    REQUIRE(ownedVehicles[0]->getRegistration() == testRegistrationValueA);
                    REQUIRE(ownedVehicles[1]->getRegistration() == testRegistrationValueB);
                    REQUIRE(ownedVehicles[2]->getRegistration() == testRegistrationValueC);

                    delete[] ownedVehicles;
                }

                AND_WHEN("A forth vehicle is added") {
                    THEN("An exception is thrown") {
                        REQUIRE_THROWS_AS(testPerson.addVehicle(*testVehicleD), PersonException);
                    }
                }

                AND_WHEN("The function to release vehicles is called on an owned vehicle") {
                    testPerson.releaseVehicle(*testVehicleB);
                    
                    THEN("The vehicle is removed and the count and the order of the owned ones changes") {
                        VehiclePtr* ownedVehicles = testPerson.getVehicles();

                        REQUIRE(testPerson.getVehiclesCount() == 2);
                        REQUIRE(ownedVehicles[0]->getRegistration() == testRegistrationValueA);
                        REQUIRE(ownedVehicles[1]->getRegistration() == testRegistrationValueC);

                        delete[] ownedVehicles;
                    }
                }

                AND_WHEN("The function to release vehicle is called on a not owned vehicle") {
                    THEN("An exception is thrown and no vehicle is removed") {
                        REQUIRE_THROWS_AS(testPerson.releaseVehicle(*testVehicleD), PersonException);

                        VehiclePtr* ownedVehicles = testPerson.getVehicles();
                        
                        REQUIRE(testPerson.getVehiclesCount() == 3);
                        REQUIRE(ownedVehicles[0]->getRegistration() == testRegistrationValueA);
                        REQUIRE(ownedVehicles[2]->getRegistration() == testRegistrationValueC);

                        delete[] ownedVehicles;
                    }
                }
            }
        }
    }
}

SCENARIO("Testing getting pointer (operator*) to person", "[operator]") {
    GIVEN("A valid person") {
        std::string testPersonName = "test owner's name";
        unsigned int testPersonID = 1;
        Person testPerson(testPersonName, testPersonID);

        THEN("The methods can be called through the pointer") {
            REQUIRE((*testPerson)->getID() == testPersonID);
        }
    }
}
