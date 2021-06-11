#include "Database.h"
#include "Registration.h"

/*#include "catch2.h"

TEST_CASE("Registration constructors")
{
    Registration r1("CA1240AB");
    Registration r2("C1235AL");
    Registration r3(r2);
    REQUIRE( r1.getReg() == "CA1240AB");
    REQUIRE( r2.getReg() == "C1235AL");
    REQUIRE( r2.getReg() == r3.getReg());
}
TEST_CASE("Registration operator==")
{
    Registration r1("CA1240AB");
    Registration r2("C1235AL");
    Registration r3(r2);
    Registration r4("CA1240AB");
    REQUIRE ( ( r1 == r4 ) == true );
    REQUIRE ( ( r2 == r3 ) == true );
    REQUIRE ( ( r1 == r2 ) == false );
}

TEST_CASE("Person default constructor")
{
    Person a;
    REQUIRE ( a.getName() == "" );
    REQUIRE ( a.getId() == 0 );
}
TEST_CASE("Person argument constructor")
{
    Person b("Pesho Peshev", 0441);
    REQUIRE( b.getName() == "Pesho Peshev");
    REQUIRE( b.getId() == 0441);
}
TEST_CASE("Vehicle constructors")
{
    Registration r2("C1235AL");
    Vehicle v1(r2, "great");
    REQUIRE(v1.getReg(). getReg() == r2.getReg());
}
TEST_CASE("Base class Splitline method")
{
    std::string tmp = "check interval removal function";
    std::vector<std::string> res = Base::splitLine(tmp);
    REQUIRE(res[0] == "check");
    REQUIRE(res[1] == "interval");
    REQUIRE(res[2] == "removal");
    REQUIRE(res[3] == "function");
}
TEST_CASE("Database addPerson method")
{
    Database* startDatabase = new Database(std::cin, std::cout);
    startDatabase->addPerson({"", "Iva" ,"Ivan", "14423"});
    startDatabase->addPerson({"", "Ivan4o" ,"Ivan", "14523"});
    startDatabase->addPerson({"", "Iva4o" ,"Ivan", "14323"});
    startDatabase->addPerson({"", "Ivancho" ,"Ivan", "1423"});
    REQUIRE(startDatabase->countPeople() == 4);
}
TEST_CASE("Database addVehicle method")
{
    Database* startDatabase = new Database(std::cin, std::cout);
    startDatabase->addVehicle({"", "CA1233PA", "brand new"});
    startDatabase->addVehicle({"", "BT5513OP" ,"old"});
    startDatabase->addVehicle({"", "CO8712OC" ,"perfect"});
    startDatabase->addVehicle({"", "B7551KA", "amazing"});
    REQUIRE(startDatabase->countVehicles() == 4);
}
TEST_CASE("Database aquire method")
{
    Database* startDatabase = new Database(std::cin, std::cout);
    startDatabase->addVehicle({"", "CA1233PA", "brand new"});
    startDatabase->addVehicle({"", "BT5513OP" ,"old"});
    startDatabase->addVehicle({"", "CO8712OC" ,"perfect"});
    startDatabase->addVehicle({"", "B7551KA", "amazing"});
    startDatabase->addPerson({"", "Ivan4o" ,"Ivan", "14523"});
    startDatabase->addPerson({"", "Iva4o" ,"Ivan", "14323"});
    startDatabase->addPerson({"", "Ivancho" ,"Ivan", "1423"});

    startDatabase->aquireVehicle({"", "1423", "CA1233PA"});
    REQUIRE(startDatabase->getPerson("1423").getCarRegs().size() == 1);
    startDatabase->aquireVehicle({"", "1423", "B7551KA"});
    REQUIRE(startDatabase->getPerson("1423").getCarRegs().size() == 2);
}
TEST_CASE("Database release method")
{
    Database* startDatabase = new Database(std::cin, std::cout);
    startDatabase->addVehicle({"", "CA1233PA", "brand new"});
    startDatabase->addVehicle({"", "BT5513OP" ,"old"});
    startDatabase->addVehicle({"", "CO8712OC" ,"perfect"});
    startDatabase->addVehicle({"", "B7551KA", "amazing"});
    startDatabase->addPerson({"", "Ivan4o" ,"Ivan", "14523"});
    startDatabase->addPerson({"", "Iva4o" ,"Ivan", "14323"});
    startDatabase->addPerson({"", "Ivancho" ,"Ivan", "1423"});

    startDatabase->aquireVehicle({"", "1423", "CA1233PA"});
    REQUIRE(startDatabase->getPerson("1423").getCarRegs().size() == 1);
    startDatabase->aquireVehicle({"", "1423", "B7551KA"});
    REQUIRE(startDatabase->getPerson("1423").getCarRegs().size() == 2);
    startDatabase->releaseVehicle({"", "1423", "CA1233PA"});
    REQUIRE(startDatabase->getPerson("1423").getCarRegs().size() == 1);
    startDatabase->releaseVehicle({"", "1423", "B7551KA"});
    REQUIRE(startDatabase->getPerson("1423").getCarRegs().size() == 0);
}
*/

int main()
{

    Base* startDatabase = new Database(std::cin, std::cout);

	try
	{
        startDatabase->start();
	}
	catch (...)
	{
		std::cout << std::endl << "Something went wrong! Terminating...";
	}

	delete startDatabase;
	return 0;
    //system("pause");

}
/*
FOR THE USER:

open /bin/data/1.txt
IF you want to run the tests:
    1) link the catch2.cpp file
    2) uncomment the catch2.h include
*/
