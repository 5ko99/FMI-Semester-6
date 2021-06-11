#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "commands.h"

TEST_CASE("Registration")
{
    SECTION("Validation")
    {
        std::string reg21("S1234DA");
        std::string reg22("AS1234DA");

        std::string reg1("s1234DA");
        std::string reg2("SHESTICA");
        std::string reg3("aS1234DA");
        std::string reg4("DA12A3BA");
        std::string reg5("31231212");
        std::string reg6("huofqawpoohfpaweufhpe");
        std::string reg7("");
        std::string reg8("S1234DAA");

        std::string list[8] = {reg1,reg2,reg3,reg4,reg5,reg6,reg7,reg8};
        
        
        for (size_t i = 0; i < 8; ++i) 
        {
            bool gotException = true;
            try 
            {
                Registration reg(list[i]);
                gotException = false;
            }
            catch(const std::invalid_argument& e) 
            {
                ;
            }
            REQUIRE(gotException);
        }

        Registration validReg1(reg21);
        Registration validReg2(reg22);

        REQUIRE(true); //Tests if the program is still running
        
    }
}

TEST_CASE("Vehicle")
{
    std::string registrationStr1 = "SA1234DA";
    Registration reg1(registrationStr1);
    std::string descr1 = "Slow car";

    std::string registrationStr2 = "BT3125NE";
    Registration reg2(registrationStr1);
    std::string descr2 = "Fast car";

    unsigned int uniqueIndex = 41968;
    Person p("Gosho", uniqueIndex);

    SECTION("Constructors")
    {
        Vehicle v1(reg1, descr1);
        Vehicle v2(reg2, descr2, uniqueIndex);

        REQUIRE(v1.getRegistration().getString() == registrationStr1);

        REQUIRE(v1.getDescription() == descr1);

        REQUIRE(v1.isThereAnOwner() == false);

        REQUIRE(v2.isThereAnOwner() == true);

        Vehicle v3(v1);

        REQUIRE(v3.getRegistration().getString() == registrationStr1);

        REQUIRE(v3.getDescription() == descr1);

        REQUIRE(v3.isThereAnOwner() == false);
    }

    SECTION("Operator =")
    {
        Vehicle v1(reg1, descr1);
        Vehicle v2(reg2, descr2, uniqueIndex);

        v2 = v1;

        REQUIRE(v2.getRegistration().getString() == registrationStr1);

        REQUIRE(v2.getDescription() == descr1);

        REQUIRE(v2.isThereAnOwner() == false);
    }

    SECTION("Add and erease owner")
    {
        Vehicle v1(reg1, descr1);
        Vehicle v2(reg2, descr2, uniqueIndex);

        v1.insertOwner(p);
        v2.eraseOwner();

        REQUIRE(v1.isThereAnOwner() == true);
        REQUIRE(v2.isThereAnOwner() == false);
    }
}

TEST_CASE("Person")
{
    std::string name1 = "Galena";
    unsigned int uniqueIndex1 = 41968;

    std::string name2 = "Medi";
    unsigned int uniqueIndex2 = 1;


    SECTION("Constructors")
    {
        Person p1(name1, uniqueIndex1);

        REQUIRE(p1.getName() == name1);

        REQUIRE(p1.getId() == uniqueIndex1);

        Person p2(p1);

        REQUIRE(p2.getName() == name1);

        REQUIRE(p2.getId() == uniqueIndex1);
    }

    SECTION(".getElement(size_t pos)")
    {
        Person p1(name1, uniqueIndex1);

        bool gotException = true;
        try
        {
            p1.getElement(333333);
            gotException = false;
        }
        catch(const std::out_of_range& e)
        {
            ;
        }
        REQUIRE(gotException);
    }

    SECTION("Insert/erease vehicle")
    {
        Person p1(name1, uniqueIndex1);

        p1.insertVehicle({Registration("DA1234SA"), "Trikolka"});

        REQUIRE(strcmp(p1.getElement(0).c_str(), "DA1234SA") == 0);

        p1.eraseVehicle({Registration("DA1234SA"), "Trikolka"});

        bool gotException = true;
        try
        {
            p1.getElement(0);
            gotException = false;
        }
        catch(const std::out_of_range& e)
        {
            ;
        }
        REQUIRE(gotException);
    }
}

TEST_CASE("Data class")
{
    Data data;

    data.addVehicle(Registration("P2118KN"), "mercedes");
    data.addVehicle(Registration("BT2222KN"), "lambo");
    data.addVehicle(Registration("P4689PP"), "motor");
    data.addVehicle(Registration("P7612HH"), "nissan");

    data.addPerson("Sasho", 6);
    data.addPerson("Deqn", 4);
    data.addPerson("Cveti", 100);

    
    SECTION(".addVehicle(), .addPerson()")
    {
        Data testData;

        testData.addVehicle(Registration("P2118KN"), "mercedes");
        testData.addVehicle(Registration("BT2222KN"), "lambo");
        testData.addVehicle(Registration("P4689PP"), "motor");

        REQUIRE(testData.getVehicleAt(0).getRegistration().getString() == "P2118KN");
        REQUIRE(testData.getVehicleAt(1).getRegistration().getString() == "BT2222KN");
        REQUIRE(testData.getVehicleAt(2).getRegistration().getString() == "P4689PP");

        testData.addPerson("Sasho", 6);
        testData.addPerson("Deqn", 4);

        REQUIRE(testData.getPersonAt(0).getId() == 6);
        REQUIRE(testData.getPersonAt(1).getId() == 4);
    }

    SECTION(".acquire(), .release(), .remove()")
    {
        SECTION(".acquire()")
        {
            data.acquire(6, Registration("P2118KN"));
            data.acquire(6, Registration("BT2222KN"));
            data.acquire(4, Registration("P7612HH"));
            data.acquire(100, Registration("P4689PP"));

            REQUIRE(data.getPersonAt(0).getOwnedVehiclesCount() == 2); //Sasho
            REQUIRE(data.getPersonAt(0).getElement(0) == "P2118KN"); //Mercedes
            REQUIRE(data.getPersonAt(0).getElement(1) == "BT2222KN"); //Lambo
            REQUIRE(data.getPersonAt(1).getOwnedVehiclesCount() == 1); //Deqn
            REQUIRE(data.getPersonAt(1).getElement(0) == "P7612HH"); //Nissan
            REQUIRE(data.getPersonAt(2).getOwnedVehiclesCount() == 1); //Cveti
            REQUIRE(data.getPersonAt(2).getElement(0) == "P4689PP"); //Motor 
        }

        SECTION(".release()")
        {
            data.release(4, Registration("P7612HH")); //Deqn, Nissan

            REQUIRE(data.getPersonAt(1).getOwnedVehiclesCount() == 0); //Deqn's cars

            REQUIRE(data.getVehicleAt(3).isThereAnOwner() == false); //Nissan
        }

        SECTION(".remove()")
        {
            data.remove(std::string("4"));

            //Deqn is removed, here has to be Cveti
            REQUIRE(data.getPersonAt(1).getId() == 100);

            REQUIRE(data.getPeopleSize() == 2);

            data.remove(std::string("100")); //Cveti

            REQUIRE(data.getPeopleSize() == 1);

            REQUIRE(data.getVehicleAt(2).isThereAnOwner() == false);

            data.remove("P4689PP"); //Motor

            REQUIRE(data.getVehicleSize() == 3);
        }
    }

    SECTION("Saving and loading from file")
    {
        data.acquire(6, Registration("P2118KN"));
        data.acquire(6, Registration("BT2222KN"));
        data.acquire(4, Registration("P7612HH"));
        data.acquire(100, Registration("P4689PP"));
        
        std::string testfilePath("Testfile.txt");
        data.saveToFile(testfilePath);

        Data testData(testfilePath);

        REQUIRE(testData.getPersonAt(0).getId() == 6);
        REQUIRE(testData.getPersonAt(1).getId() == 4);
        REQUIRE(testData.getPersonAt(2).getId() == 100);

        REQUIRE(testData.getVehicleAt(0).getRegistration().getString() == "P2118KN");
        REQUIRE(testData.getVehicleAt(1).getRegistration().getString() == "BT2222KN");
        REQUIRE(testData.getVehicleAt(2).getRegistration().getString() == "P4689PP");
        REQUIRE(testData.getVehicleAt(3).getRegistration().getString() == "P7612HH");
    }

    SECTION("Extracting arguments")
    {
        Data tempData; 
        std::string command("release 22223 P2118KN");

        std::string first;
        std::string second;
        std::string third;

        getAllArguments(command, first, second, third); 

        REQUIRE(first == "release");
        REQUIRE(second == "22223");
        REQUIRE(third == "P2118KN");

        command = "person 123 \"\"Ivan Ivanov\"\"\"";

        first.clear();
        second.clear();
        third.clear();

        getAllArguments(command, first, second, third); 

        REQUIRE(first == "person");
        REQUIRE(second == "123");
        REQUIRE(third == "\"Ivan Ivanov\"\"");

        first.clear();
        second.clear();
        third.clear();

        
        bool gotException = true;
        try
        {
            command = "banan   \"\"Ivan Ivanov\"\"\" \"Ivan Ivanov";
            getAllArguments(command, first, second, third); 
            gotException = false; 
        }
        catch(const std::exception& e)
        {
            REQUIRE(gotException); 
        }
        

    }

}
