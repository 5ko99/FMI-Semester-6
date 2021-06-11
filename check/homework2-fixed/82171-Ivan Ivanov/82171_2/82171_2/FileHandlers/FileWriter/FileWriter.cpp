#include "FileWriter.h"
#include "../../CommandInterpreter/CommandInterpreter.h"
#include <iostream>

void FileWriter::writeToFile(std::string fileAddress, PersonHolder* pH, VehicleHolder* vH) {
    std::ifstream testExists;
    testExists.open(fileAddress);
    if(testExists) {
        std::cout << "File already exists." << std::endl;
        if (CommandInterpreter::confirmCommand() == false) {
            testExists.close();
            return;
        }
    }
    testExists.close();

    std::ofstream file(fileAddress);
    std::vector<Person> people = pH->getAllPeople();
    std::vector<Vehicle> vehicles = vH->getAllVehicles();

    for (std::size_t i = 0; i < people.size(); ++i) {
        file << "PERSON \"" << people.at(i).getName() << "\" \"" << people.at(i).getID() << "\"" << std::endl;
    }

    for (std::size_t i = 0; i < vehicles.size(); ++i) {
        file << "VEHICLE \"" << vehicles.at(i).getRegistration() << "\" \"" << vehicles.at(i).getDescription() << "\"" << std::endl;
        file << "ACQUIRE \"" <<vehicles.at(i).getOwner()->getID() << "\" \"" << vehicles.at(i).getRegistration() << "\"" << std::endl;
    }

    file.close();
}
