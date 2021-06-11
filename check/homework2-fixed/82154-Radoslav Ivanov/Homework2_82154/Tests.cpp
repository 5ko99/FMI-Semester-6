#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "program.h"

TEST_CASE ("Testing Registration")
{
    SECTION ("Registration::validateRegistration"){
        REQUIRE(Registration::validateRegistration(std::string("ab1234ab")) == true);
        REQUIRE(Registration::validateRegistration(std::string("Ab1234BA")) == true);
        REQUIRE(Registration::validateRegistration(std::string("A1234as")) == true);
        REQUIRE(Registration::validateRegistration(std::string("as1234a")) == false);
        REQUIRE(Registration::validateRegistration(std::string("as12345as")) == false);
        REQUIRE(Registration::validateRegistration(std::string("aBc1234as")) == false);
        REQUIRE(Registration::validateRegistration(std::string("a77777as")) == false);
    }

    SECTION ("copy constructor, operator= and operator=="){
        Registration reg1("A2202KM");
        Registration reg2;
        reg2 = reg1;
        REQUIRE (reg1 == reg2);
        Registration reg_copy(reg2);
        REQUIRE (reg_copy == reg1);
        Registration smallLettersReg("a2202kM");
        REQUIRE (smallLettersReg == reg1);
        Registration another_reg("TA2202KA");
        REQUIRE (!( another_reg == reg1 ));
    }
}


TEST_CASE ("Testing Vehicle")
{
    Vehicle defaultVeh;
    REQUIRE (defaultVeh.getOwner() == nullptr);
    REQUIRE (defaultVeh.getDescript().size() == 0);
    REQUIRE (defaultVeh.getRegistration() == Registration("UNKNOWN"));
        
    Vehicle vehicle(Registration("TK1234KA"), "BMW X5");
    REQUIRE (vehicle.getOwner() == nullptr);
    REQUIRE (vehicle.getDescript() == "BMW X5");
    REQUIRE (vehicle.getRegistration() == Registration("TK1234KA"));
    Person owner("Orlin Kirilov", 850205123);
    vehicle.addOwner(owner);
    owner.addVehicle(vehicle);
    REQUIRE (vehicle.getOwner() == &owner);

    Vehicle veh_copy(vehicle);
    REQUIRE (veh_copy.getOwner() == &owner);
    REQUIRE (veh_copy.getDescript() == "BMW X5");
    REQUIRE (veh_copy.getRegistration() == Registration("TK1234KA"));
        
    Person newOwner("Kamen Ivanovic", 123456789);
    vehicle.addOwner(newOwner);
    newOwner.addVehicle(vehicle);
    REQUIRE (vehicle.getOwner() == &newOwner);

    vehicle.releaseOwner();
    REQUIRE (vehicle.getOwner() == nullptr);
}


TEST_CASE ("Testing Person")
{
    Person defaultPer;
    REQUIRE (!defaultPer.hasAnyVehicles());

    Person Slavi ("Slavi Panayotov", 1234567);
    REQUIRE (Slavi.getName() == "Slavi Panayotov");
    REQUIRE (Slavi.getId() == 1234567);
    REQUIRE (Slavi.hasAnyVehicles() == false);
    REQUIRE (Slavi.getCountOfVehs() == 0);

    Vehicle v1(Registration("A1234AA"), "Cool car");
    Slavi.addVehicle(v1);
    v1.addOwner(Slavi);
    REQUIRE (Slavi.getCountOfVehs() == 1);
    
    Vehicle v2(Registration("GB8902KA"), "Pretty car");
    Vehicle v3(Registration("SA1700DA"), "Big Truck");
    Slavi.addVehicle(v2); v2.addOwner(Slavi);
    Slavi.addVehicle(v3); v3.addOwner(Slavi);

    REQUIRE (Slavi.getCountOfVehs() == 3);
    for (int i=0; i<Slavi.getCountOfVehs(); ++i){
        REQUIRE (Slavi.getOwnedVehicle(i)->getOwner() == &Slavi);
    }

    REQUIRE (Slavi.getOwnedVehicle(1)->getRegistration() == Registration("GB8902KA"));
    REQUIRE (Slavi.getOwnedVehicle(2)->getDescript() == "Big Truck");

    Slavi.releaseVehicle(Registration("GB8902KA"));
    REQUIRE (Slavi.getCountOfVehs() == 2);
    Slavi.releaseAllVehicles();
    REQUIRE (Slavi.hasAnyVehicles() == false);
}


TEST_CASE ("Testing AllVehicles")
{
    SECTION ("Adding Vehicles")
    {
        AllVehicles AV;
        REQUIRE (AV.getCount() == 0);
        Vehicle v1(Registration("SA1234AS"), "First Vehicle");
        AV.addVehicle(v1);
        REQUIRE (AV.getCount() == 1);
        Vehicle v2(Registration("VT7777KA"), "Second Vehicle");
        AV.addVehicle(v2);
        REQUIRE (AV.getCount() == 2);
        Vehicle v_sameReg (Registration("SA1234AS"), "Same Registration");
        REQUIRE_THROWS_AS (AV.addVehicle(v_sameReg), std::invalid_argument);
        REQUIRE (AV.getCount() == 2);
    }
    
    SECTION ("Operator[] and getVehicle()")
    {
        AllVehicles AV;
        Vehicle v1(Registration("AA1111AA"), "First");
        Vehicle v2(Registration("BB2222BB"), "Second");
        AV.addVehicle(v1);
        AV.addVehicle(v2);
        REQUIRE (AV[0]->getOwner() == nullptr);
        REQUIRE (AV[0]->getRegistration() == Registration("AA1111AA"));
        REQUIRE (AV[0]->getDescript() == "First");
        REQUIRE (AV[1]->getOwner() == nullptr);
        REQUIRE (AV[1]->getRegistration() == Registration("BB2222BB"));
        REQUIRE (AV[1]->getDescript() == "Second");
        REQUIRE (AV.getVehicle(Registration("BB2222BB")) == AV[1]);
    }

    SECTION ("Adding owners, Removing and releasing")
    {     
        AllVehicles AV;
        Vehicle v1(Registration("AA1111AA"), "First");
        Vehicle v2(Registration("BB2222BB"), "Second");
        Vehicle v3(Registration("CC3333CC"), "Third");
        AV.addVehicle(v1);
        AV.addVehicle(v2);
        AV.addVehicle(v3);
        REQUIRE (AV.getCount() == 3);
        Person owner1("Ivan Ivanov", 123);

        AV.addOwnerToVehicle(Registration("AA1111AA"), owner1);
        owner1.addVehicle(*AV[0]);

        REQUIRE (AV.getVehicle(Registration("AA1111AA"))->getOwner() == &owner1);
      
        REQUIRE_THROWS_AS (AV.addOwnerToVehicle(Registration("SS1234SS"), owner1), std::invalid_argument);
        REQUIRE_THROWS_AS ((AV.getVehicle(Registration("AA1111AB"))->getOwner() == &owner1), std::invalid_argument);
        REQUIRE_THROWS_AS (AV.releaseOwnerFromVehicle(Registration("S1111SS")), std::invalid_argument);
        
        AV.releaseOwnerFromVehicle(Registration("AA1111AA"));
        REQUIRE (AV.getVehicle(Registration("AA1111AA"))->getOwner() == nullptr);
  
        AV.removeVehicle(Registration("BB2222BB"));
        REQUIRE (AV.getCount() == 2);
        REQUIRE_THROWS_AS (AV.removeVehicle(Registration("BB2222BB")), std::invalid_argument);   
    }
}


TEST_CASE ("Testing People")
{
    SECTION ("Adding people")
    {
        People ppl;
        REQUIRE (ppl.getCount() == 0);
        Person arr[5] = {Person ("Radoslav Cvetanov", 123), 
                         Person ("Hitur Peter Petrov", 124),
                         Person ("Atanas Dalchev", 125),
                         Person ("Rendi Ortan", 126),
                         Person ("Hitromir Hitrev", 127)};
        for (int i=0; i<5; ++i){
            ppl.addPerson(arr[i]);
            REQUIRE (ppl[i]->getName() == arr[i].getName());
            REQUIRE (ppl[i]->getId() == arr[i].getId());
        }
        REQUIRE (ppl.getCount() == 5);

        REQUIRE_THROWS_AS (ppl.addPerson(arr[1]), std::invalid_argument);
        Person bait("New ButNot", 124);
        REQUIRE_THROWS_AS (ppl.addPerson(bait), std::invalid_argument);
        
        Person newOne("Rendi Ortan", 128); //same name, but another id. Shouldnt be a problem
        REQUIRE_NOTHROW (ppl.addPerson(newOne));
    }
    
    SECTION ("Adding vehicles, releasing and removing")
    {
        People ppl;
        Person p1("Niki Mihaylov", 220);
        Person p2("Mihail Gorbachov", 1991);
        ppl.addPerson(p1); 
        ppl.addPerson(p2);
        REQUIRE (ppl.getCount() == 2);
        Vehicle vehs[6] = {Vehicle(Registration("AB1234AB"), "Vehicle1"),
                          Vehicle(Registration("AS5678AB"), "Vehicle2"),
                          Vehicle(Registration("A0000AB"), "Vehicle3"),
                          Vehicle(Registration("B1448AB"), "Vehicle4"),
                          Vehicle(Registration("ED1111NO"), "Vehicle5"),
                          Vehicle(Registration("P5555ET"), "Vehicle6")};

        for (int i=0; i<6; ++i){
            ppl.addVehicleToPerson(vehs[i], 220);
            vehs[i].addOwner(*ppl[0]);
            REQUIRE (ppl[0]->getOwnedVehicle(i)->getOwner() == ppl[0]);
            REQUIRE (ppl[0]->getOwnedVehicle(i)->getRegistration() == vehs[i].getRegistration());
            REQUIRE (ppl[0]->getOwnedVehicle(i)->getDescript() == vehs[i].getDescript());
        }
        REQUIRE (ppl[0]->getCountOfVehs() == 6);
        REQUIRE_THROWS_AS (ppl.addVehicleToPerson(vehs[2], 220), std::logic_error); //adding the same vehicle 2 times
        REQUIRE (ppl[0]->getCountOfVehs() == 6);
        
        Vehicle bait (Registration("ED1111NO"), "New butNot New"); //same reg, different descript
        REQUIRE_THROWS_AS (ppl.addVehicleToPerson(bait, 220), std::logic_error);

        Vehicle newOne (Registration("N9999EW"), "Vehicle1"); //same descript, but another reg
        newOne.addOwner(*ppl[0]);
        REQUIRE_NOTHROW (ppl.addVehicleToPerson(newOne, 220));
        REQUIRE (ppl[0]->getCountOfVehs() == 7);

        ppl.releaseVehicleFromPerson(Registration("P5555ET"), 220);
        REQUIRE (ppl[0]->getCountOfVehs() == 6);
        REQUIRE_THROWS_AS (ppl.releaseVehicleFromPerson(Registration("EX7821KL"), 220), std::invalid_argument); //person does not own this vehicle
        REQUIRE_THROWS_AS (ppl.releaseVehicleFromPerson(Registration("A0000AB"), 2021), std::invalid_argument); //unexisting person
        ppl.removePerson(220);
        REQUIRE (ppl.getCount() == 1);
    }

}

TEST_CASE ("Testing Commands")
{
    SECTION ("Testing static functions")
    {
        std::string str("ABcDEF");
        Commands::toLowerCase(str);
        REQUIRE (str == "abcdef");

        str = "abc12D222";
        Commands::toLowerCase(str);
        REQUIRE (str == "abc12d222");

        REQUIRE (Commands::whatIsThis(str) == 0);
        str = "12345678";
        REQUIRE (Commands::whatIsThis(str) == 1);
        str = "A1234AB";
        REQUIRE (Commands::whatIsThis(str) == 2);
        str.push_back('a');
        REQUIRE (Commands::whatIsThis(str) == 0);
    }

    Commands cmds;

    SECTION ("Default")
    {
        REQUIRE (cmds.getAV().getCount() == 0);
        REQUIRE (cmds.getPPL().getCount() == 0);
    }

    SECTION ("Adding vehicles")
    {
        cmds.VEHICLE(Registration("AB1234AB"), "Eins");
        REQUIRE (cmds.getAV().getCount() == 1);
        REQUIRE (cmds.getAV().getVehicle(Registration("AB1234AB"))->getDescript() == "Eins");
        REQUIRE (cmds.getAV().getVehicle(Registration("AB1234AB"))->getOwner() == nullptr);
        cmds.VEHICLE(Registration("ED1111NO"), "Zwei");
        REQUIRE (cmds.getAV().getCount() == 2);
        //Trying to add vehicle with the same registration
        REQUIRE_THROWS (cmds.VEHICLE(Registration("ED1111NO"), "Doppel Zwei"));
        REQUIRE (cmds.getAV().getCount() == 2);
        cmds.VEHICLE(Registration("JK4545JK"), "Drei");
        REQUIRE (cmds.getAV().getCount() == 3);
    }

    SECTION ("Adding people")
    {
        cmds.PERSON("Osman Pasha", 1234);
        REQUIRE (cmds.getPPL().getCount() == 1);
        REQUIRE (cmds.getPPL().getPerson(1234)->getName() == "Osman Pasha");
        REQUIRE (cmds.getPPL().getPerson(1234)->getCountOfVehs() == 0); //has no vehicles
        cmds.PERSON("Ivan Asen II", 12181241);
        REQUIRE (cmds.getPPL().getCount() == 2);
        //Trying to add person with the same id
        REQUIRE_THROWS (cmds.PERSON("Nov Ivan Asen", 12181241));
        REQUIRE (cmds.getPPL().getCount() == 2);
    }

    SECTION ("Acquiring")
    {
        //Starting base
        cmds.VEHICLE(Registration("AB1234AB"), "Eins");
        cmds.VEHICLE(Registration("ED1111NO"), "Zwei");
        cmds.VEHICLE(Registration("JK4545JK"), "Drei");
        cmds.PERSON("Osman Pasha", 1234);
        cmds.PERSON("Ivan Asen II", 12181241);


        cmds.ACQUIRE(1234, Registration("AB1234AB"));
        REQUIRE (cmds.getPPL().getPerson(1234)->getCountOfVehs() == 1);
        REQUIRE (cmds.getAV().getVehicle(Registration("AB1234AB"))->getOwner() == cmds.getPPL().getPerson(1234));
        //Changing owner
        cmds.ACQUIRE(12181241, Registration("AB1234AB"));
        REQUIRE (cmds.getPPL().getPerson(1234)->getCountOfVehs() == 0);
        REQUIRE (cmds.getPPL().getPerson(12181241)->getCountOfVehs() == 1);
        REQUIRE (cmds.getAV().getVehicle(Registration("AB1234AB"))->getOwner() == cmds.getPPL().getPerson(12181241));
        //Trying to acquire a vehicle to an unexisting person
        REQUIRE_THROWS (cmds.ACQUIRE(111111, Registration("AB1234AB")));
        REQUIRE (cmds.getPPL().getPerson(12181241)->getCountOfVehs() == 1);
        REQUIRE (cmds.getAV().getVehicle(Registration("AB1234AB"))->getOwner() == cmds.getPPL().getPerson(12181241));
        //Trying to acquire an unexisting vehicle to a person
        REQUIRE_THROWS (cmds.ACQUIRE(12181241, Registration("NO1234NO")));
        REQUIRE (cmds.getPPL().getPerson(12181241)->getCountOfVehs() == 1);

        cmds.ACQUIRE (12181241, Registration("JK4545JK"));
        REQUIRE (cmds.getPPL().getPerson(12181241)->getCountOfVehs() == 2);
        cmds.ACQUIRE (1234, Registration("ED1111NO"));
        REQUIRE (cmds.getPPL().getPerson(1234)->getCountOfVehs() == 1);
    }

    SECTION ("Releasing")
    {
        //Starting base
        cmds.VEHICLE(Registration("AB1234AB"), "Eins");
        cmds.VEHICLE(Registration("ED1111NO"), "Zwei");
        cmds.VEHICLE(Registration("JK4545JK"), "Drei");
        cmds.PERSON("Osman Pasha", 1234);
        cmds.PERSON("Ivan Asen II", 12181241);
        cmds.ACQUIRE (1234, Registration("ED1111NO"));
        cmds.ACQUIRE(12181241, Registration("AB1234AB"));
        cmds.ACQUIRE (12181241, Registration("JK4545JK"));


        //Trying to release an unexistring vehicle
        REQUIRE_THROWS_AS (cmds.RELEASE(1234, Registration("XX4444XX")), std::invalid_argument);
        REQUIRE (cmds.getPPL().getPerson(1234)->getCountOfVehs() == 1);
        //Trying to release a vehicle that is not owned by the person
        REQUIRE_THROWS_AS (cmds.RELEASE(1234, Registration("AB1234AB")), std::invalid_argument);
        REQUIRE (cmds.getPPL().getPerson(1234)->getCountOfVehs() == 1);
        REQUIRE (cmds.getAV().getVehicle(Registration("AB1234AB"))->getOwner() == cmds.getPPL().getPerson(12181241));
        //Trying to release a vehicle from unexisting person
        REQUIRE_THROWS_AS (cmds.RELEASE(77777, Registration("AB1234AB")), std::invalid_argument);
        REQUIRE (cmds.getAV().getVehicle(Registration("AB1234AB"))->getOwner() == cmds.getPPL().getPerson(12181241));
        
        cmds.RELEASE(1234, Registration("ED1111NO"));
        REQUIRE (cmds.getPPL().getPerson(1234)->getCountOfVehs() == 0);
        REQUIRE (cmds.getAV().getVehicle(Registration("ED1111NO"))->getOwner() == nullptr);
    }

    SECTION ("Saving")
    {
        //Starting base
        cmds.VEHICLE(Registration("AB1234AB"), "Eins");
        cmds.VEHICLE(Registration("ED1111NO"), "Zwei");
        cmds.VEHICLE(Registration("JK4545JK"), "Drei");
        cmds.PERSON("Osman Pasha", 1234);
        cmds.PERSON("Ivan Asen II", 12181241);
        cmds.ACQUIRE(12181241, Registration("AB1234AB"));
        cmds.ACQUIRE (12181241, Registration("JK4545JK"));


        std::ofstream dataFile ("saved.txt", std::ios::trunc);
        if (!dataFile.is_open()){
            throw std::runtime_error("Unable to open file"); 
        } 
                        //The data in the file should be:
        std::string arr[7] = {"VEHICLE AB1234AB \"Eins\"",
                              "VEHICLE ED1111NO \"Zwei\"",
                              "VEHICLE JK4545JK \"Drei\"",
                              "PERSON \"Osman Pasha\" 1234",
                              "PERSON \"Ivan Asen II\" 12181241",
                              "ACQUIRE 12181241 AB1234AB",
                              "ACQUIRE 12181241 JK4545JK"};
        cmds.SAVE(dataFile);
        dataFile.close();

        std::ifstream iFile ("saved.txt");
        if (!iFile.is_open()){
            throw std::runtime_error("Unable to open file"); 
        } 
        for (int i=0; i<7; ++i){
            std::string command;    
            getline (iFile, command);
            REQUIRE (command == arr[i]);
        }
        char x;
        iFile >> x; //to get iFile.eof() activated
        REQUIRE (iFile.eof());
        iFile.close();
    }

    SECTION ("Removing")
    {
        //Starting base
        cmds.VEHICLE(Registration("AB1234AB"), "Eins");
        cmds.VEHICLE(Registration("ED1111NO"), "Zwei");
        cmds.VEHICLE(Registration("JK4545JK"), "Drei");
        cmds.PERSON("Osman Pasha", 1234);
        cmds.PERSON("Ivan Asen II", 12181241);
        cmds.ACQUIRE(12181241, Registration("AB1234AB"));
        cmds.ACQUIRE (12181241, Registration("JK4545JK"));


        //Trying to remove an unexisting person
        REQUIRE_THROWS_AS (cmds.REMOVE("567890"), std::invalid_argument);
        //Trying to remove an unexisting vehicle
        REQUIRE_THROWS_AS (cmds.REMOVE("X4444XX"), std::invalid_argument);
        //Remove vehicle with owner
        REQUIRE_NOTHROW (cmds.REMOVE("AB1234AB"));
        REQUIRE (cmds.getAV().getCount() == 2);
        REQUIRE (cmds.getPPL().getPerson(12181241)->getCountOfVehs() == 1);
        //Remove person with vehicle
        REQUIRE_NOTHROW (cmds.REMOVE("12181241"));
        REQUIRE (cmds.getPPL().getCount() == 1);
        REQUIRE (cmds.getAV().getVehicle(Registration("JK4545JK"))->getOwner() == nullptr);
        //Remove vehicle without owner
        REQUIRE_NOTHROW (cmds.REMOVE("JK4545JK"));
        REQUIRE (cmds.getAV().getCount() == 1);
        //Remove person without vehicles 
        REQUIRE_NOTHROW (cmds.REMOVE("1234"));
        REQUIRE (cmds.getPPL().getCount() == 0);
    }
}


TEST_CASE ("Testing program")
{
    Program p;

    //creating a file to read from
    std::ofstream file ("test.txt", std::ios::trunc);
    if (!file.is_open()){
        throw std::runtime_error("Unable to create file");
    }

    file << "vehicle qw1234qw \"First car\"\n" 
         << "veHiCle R2021KA SecondCar\n"
         << "vehicle         SP1234SP              \"S p a c e\"  \n"
         << "PERSON \"Momchil Petrov\" 200\n"
         << "pErSon Kaloyan 12345\n"
         << "person \"Dimitur Vasilev Donev\" 2001\n"
         << "acquire 200 qw1234qw\n"
         << "acQuiRe 200 r2021ka\n";

    file.close();

    //Read the file
    std::ifstream readFile ("test.txt");
    if (!readFile.is_open()){
        throw std::runtime_error("Unable to open file");
    }
    p.readFromFile(readFile);
    readFile.close();

    SECTION ("Invalid commands")
    {
        REQUIRE_THROWS(p.executeCommand(""));
        REQUIRE_THROWS(p.executeCommand("vehicle"));
        REQUIRE_THROWS(p.executeCommand("vehicle ed1111no    "));
        REQUIRE_THROWS(p.executeCommand("vehicle \"sth\" ed1111no"));
        REQUIRE_THROWS(p.executeCommand("person. Yosif 191919"));
        REQUIRE_THROWS(p.executeCommand("vehicle ed1111no Good butnotgood"));
        REQUIRE_THROWS(p.executeCommand("show qw1234qw \"First car\""));
        REQUIRE_THROWS(p.executeCommand("/@#$%^&* #%^&(* %^^&*\n \n"));
    }


    SECTION ("Vehicle and Person")
    {
        //Duplicate registration
        REQUIRE_THROWS(p.executeCommand("vehicle sp1234sp Duplicate"));
        //New vehicle
        REQUIRE_NOTHROW(p.executeCommand("vehicle ED1111NO GoodCar"));
        //Duplicate ID
        REQUIRE_THROWS(p.executeCommand("person kosio 12345"));
        //New person
        REQUIRE_NOTHROW(p.executeCommand("person \"Hristiyan Ivaylov\" 7777"));
    }

    SECTION ("Acquire and release")
    {
        //Wrong argument
        REQUIRE_THROWS(p.executeCommand("acquire 2001 AB1234AB"));
        //Switched arguments
        REQUIRE_THROWS(p.executeCommand("acquire qw1234qw 2001"));
        //acquire
        REQUIRE_NOTHROW(p.executeCommand("acquire 2001 qw1234qw"));

        //wrong argument
        REQUIRE_THROWS(p.executeCommand("release 787878 AB1234AB"));
        //switched arguments
        REQUIRE_THROWS(p.executeCommand("release r2021ka 200"));
        //release vehicle
        REQUIRE_NOTHROW(p.executeCommand("release 200 r2021ka"));
    }

    SECTION ("Remove")
    {
        //wrong argument
        REQUIRE_THROWS(p.executeCommand("remove AB1234AB"));
        REQUIRE_THROWS(p.executeCommand("remove 7777as7"));
        //remove vehicle
        REQUIRE_NOTHROW(p.executeCommand("remove SP1234SP"));
        //trying to remove already removed vehicle
        REQUIRE_THROWS(p.executeCommand("remove SP1234SP"));
        //remove person
        REQUIRE_NOTHROW(p.executeCommand("remove 200"));
        //trying to remove already removed person
        REQUIRE_THROWS(p.executeCommand("remove 200"));
    }
}
