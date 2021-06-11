#define CATCH_CONFIG_MAIN
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"catch2.hpp"
#include"commands.h"
#include"registration.h"
#include"vehicle.h"
#include"person.h"
#include"listOfPeople.h"
#include"listOfVehicles.h"

TEST_CASE("Registration", "[registration]") {

    Registration reg1("VN4347VN");
 
    REQUIRE(reg1.getRegistration().compare("VN4347VN") == 0);
    REQUIRE_THROWS(Registration("vn4347vn"));
    REQUIRE_THROWS(Registration("VN44444VN"));
    REQUIRE_THROWS(Registration("V4347V"));
    REQUIRE_THROWS(Registration("V4347vv"));
    
}

TEST_CASE("Vehicle", "[vehicle]") {

    SECTION("test the constructor") {

        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");

        REQUIRE(vehicle.getRegistration().compare("VN4347VN") == 0);
        REQUIRE(vehicle.getDescription().compare("Opel") == 0);

    }

    SECTION("test the getPerson() function without owner") {

        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");

        REQUIRE(vehicle.isItHasNoOwner() == true);
        REQUIRE_THROWS(vehicle.getPerson());

    }

    SECTION("test the getPerson() function with owner and the addPerson() function") {

        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");
        Person person("Mihail", 1234);
    
        vehicle.addPerson(&person);
        
        REQUIRE(vehicle.getPerson() != nullptr);
        REQUIRE(vehicle.isItHasNoOwner() == false);

    }

    SECTION("test releaseOwner() function") {

        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");
        Person person("Mihail", 1234);

        vehicle.addPerson(&person);
        vehicle.releaseOwner();

        REQUIRE(vehicle.isItHasNoOwner() == true);
        REQUIRE_THROWS(vehicle.getPerson());

    }

}

TEST_CASE("Person", "[person]") {

    SECTION("test the constructor") {

        Person person("Mihail", 123);

        REQUIRE(person.getName().compare("Mihail") == 0);
        REQUIRE(person.getId() == 123);
        
    }

    SECTION("test the copy constructor") {

        Person person("Mihail", 123);
        Person person2(person);

        REQUIRE(person2.getName().compare("Mihail") == 0);
        REQUIRE(person2.getId() == 123);
        REQUIRE(person2.getName().compare(person.getName()) == 0);
        REQUIRE(person2.getId() == person.getId());

    }

    SECTION("test the assignment operator") {

        Person person("Mihail", 123);
        Person person2 = person;

        REQUIRE(person2.getName().compare("Mihail") == 0);
        REQUIRE(person2.getId() == 123);
        REQUIRE(person2.getName().compare(person.getName()) == 0);
        REQUIRE(person2.getId() == person.getId());

    }

    SECTION("test addVehicle() function") {

        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");
        Person person("Mihail", 1234);

        person.addVehicle(&vehicle);

        REQUIRE(person.isHeHasNoVehicles() == false);
        REQUIRE(person.getVehicles().empty() == false);

    }

    SECTION("test releaseVehicle() function") {

        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");
        Person person("Mihail", 1234);

        person.addVehicle(&vehicle);
        person.releaseVehicle("VN4347VN");

        REQUIRE(person.getVehicles().empty() == true);
        REQUIRE(vehicle.isItHasNoOwner() == true);

    }

    SECTION("test getVehicles() function without vehicles") {

        Person person("Mihail", 123);

        REQUIRE(person.getVehicles().empty() == true);

    }

    SECTION("test getVehicles() function with vehicles") {

        Person person("Mihail", 123);
        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");

        person.addVehicle(&vehicle);

        REQUIRE(person.getVehicles().empty() == false);

    }

}

TEST_CASE("Commands", "[commands]") {

    SECTION("test executeCommand() function") {

        Commands command = Commands();
        command.checkCommands("person Mihail 123");

        REQUIRE_THROWS(command.checkCommands("Vihicle VN4347VN Opel"));
        REQUIRE_THROWS(command.checkCommands("personn Mihail 123"));
        REQUIRE_THROWS(command.checkCommands("person Mihail s"));
        REQUIRE_THROWS(command.checkCommands("acquire sss VN4347VN"));
        REQUIRE_THROWS(command.checkCommands("vehicle VM4556VM aaa aaa"));
        REQUIRE_THROWS(command.checkCommands("remove 123 Mihail"));
        REQUIRE_THROWS(command.checkCommands("person Mihail Sashkov 123"));
        REQUIRE_THROWS(command.checkCommands("release s123 VN4347VN"));
        REQUIRE_THROWS(command.checkCommands("vehicle  VO5678V Opel"));
        REQUIRE(command.getCommand().compare("person Mihail 123") == 0);

    }

    SECTION("test the getters") {
        
        Commands command = Commands();
        command.checkCommands("person Mihail 123");

        REQUIRE(command.getCommand().compare("person Mihail 123") == 0);
        REQUIRE(command.getCommandPart().compare("person") == 0);
        REQUIRE(command.getArgumentPart().compare("Mihail 123") == 0);

    }

}

TEST_CASE("ListOfPeople", "[list of people]") {

    SECTION("test addPerson() function") {

        ListOfPeople people = ListOfPeople();
        Person person("Mihail", 123);
        Person person2("Pesho", 123);

        people.addPerson(person);

        REQUIRE_THROWS(people.addPerson(person2));
        REQUIRE(people.empty() == false);
        REQUIRE(people.count() == 1);

    }

    SECTION("test getOwner() function") {
        
        ListOfPeople people = ListOfPeople();
        Person person("Mihail", 1);

        people.addPerson(person);

        REQUIRE_THROWS(people.getOwner(2));
        REQUIRE(people.getOwner(1)->getId() == 1);
        REQUIRE(people.getOwner(1)->getName().compare("Mihail") == 0);
        REQUIRE(people.count() == 1);

    }

    SECTION("test addVehicleForThePerson() function") {

        ListOfPeople people = ListOfPeople();
        ListOfVehicles vehicles = ListOfVehicles();
        Person person("Mihail", 1);
        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");

        vehicles.addVehicles(vehicle);
        people.addPerson(person);
        people.addVehicleForThePerson(vehicles.getVehicle("VN4347VN"), 1);

        REQUIRE(people.getOwner(1)->isHeHasNoVehicles() == false);
        REQUIRE(people.count() == 1);

    }

    SECTION("test releaseVehicleFromPerson() function") {

        ListOfPeople people = ListOfPeople();
        ListOfVehicles vehicles = ListOfVehicles();
        Person person("Mihail", 1);
        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");

        vehicles.addVehicles(vehicle);
        people.addPerson(person);
        people.addVehicleForThePerson(vehicles.getVehicle("VN4347VN"), 1);
        people.releaseVehicleFromPerson(1, "VN4347VN");

        REQUIRE(people.getOwner(1)->isHeHasNoVehicles() == true);
        REQUIRE(people.count() == 1);

    }

    SECTION("test removePerson() function when the list of people is empty") {

        ListOfPeople people = ListOfPeople();

        REQUIRE_THROWS(people.removePerson(1));
        REQUIRE(people.empty() == true);
        REQUIRE(people.count() == 0);

    }

    SECTION("test removePerson() function with people in the list") {

        ListOfPeople people = ListOfPeople();
        Person person("Mihail", 123);
        Person person2("Pesho", 124);

        people.addPerson(person);
        people.addPerson(person2);
        people.removePerson(123);

        REQUIRE_THROWS(people.removePerson(125));
        REQUIRE(people.empty() == false);
        REQUIRE(people.count() == 1);
        
    }

}

TEST_CASE("ListOfVehicles", "[list of vehicles]") {

    SECTION("test addVehicles() function") {

        ListOfVehicles vehicles = ListOfVehicles();
        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");
        Registration reg2("VN4347VN");
        Vehicle vehicle2(reg2, "Mazda");

        vehicles.addVehicles(vehicle);

        REQUIRE_THROWS(vehicles.addVehicles(vehicle2));
        REQUIRE(vehicles.count() == 1);
        REQUIRE(vehicles.empty() == false);

    }

    SECTION("test getVehicle() function") {

        ListOfVehicles vehicles = ListOfVehicles();
        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");

        vehicles.addVehicles(vehicle);

        REQUIRE_THROWS(vehicles.getVehicle("MM4444MM"));
        REQUIRE(vehicles.getVehicle("VN4347VN")->getRegistration().compare("VN4347VN") == 0);
        REQUIRE(vehicles.getVehicle("VN4347VN")->getDescription().compare("Opel") == 0);
        REQUIRE(vehicles.count() == 1);

    }

    SECTION("test addOwner() function") {

        ListOfPeople people = ListOfPeople();
        ListOfVehicles vehicles = ListOfVehicles();
        Person person("Mihail", 1);
        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");

        vehicles.addVehicles(vehicle);
        people.addPerson(person);
        
        vehicles.addOwner(people.getOwner(1), "VN4347VN");

        REQUIRE(vehicles.count() == 1);
        REQUIRE(vehicles.getVehicle("VN4347VN")->isItHasNoOwner() == false);
        
    }

    SECTION("test releasePerson() function") {

        ListOfPeople people = ListOfPeople();
        ListOfVehicles vehicles = ListOfVehicles();
        Person person("Mihail", 1);
        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");

        vehicles.addVehicles(vehicle);
        people.addPerson(person);
        
        vehicles.addOwner(people.getOwner(1), "VN4347VN");
        vehicles.releasePerson("VN4347VN");

        REQUIRE(vehicles.count() == 1);
        REQUIRE(vehicles.getVehicle("VN4347VN")->isItHasNoOwner() == true);

    }

    SECTION("test removeVehicle() function when the list of vehicles is empty") {

        ListOfVehicles vehicles = ListOfVehicles();

        REQUIRE_THROWS(vehicles.removeVehicle("VN4347VN"));
        REQUIRE(vehicles.empty() == true);
        REQUIRE(vehicles.count() == 0);

    }

    SECTION("test removeVehicle() function when the list of vehicles is not empty") {

        ListOfVehicles vehicles = ListOfVehicles();
        Registration reg1("VN4347VN");  
        Vehicle vehicle(reg1, "Opel");
        Registration reg2("MP5454MP");
        Vehicle vehicle2(reg2, "Mazda");

        vehicles.addVehicles(vehicle);
        vehicles.addVehicles(vehicle2);
        vehicles.removeVehicle("VN4347VN");

        REQUIRE_THROWS(vehicles.removeVehicle("SS3322ZZ"));
        REQUIRE(vehicles.count() == 1);
        REQUIRE(vehicles.empty() == false);

    }

}
