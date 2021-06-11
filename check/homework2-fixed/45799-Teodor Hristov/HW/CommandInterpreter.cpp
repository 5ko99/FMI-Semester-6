#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include "CommandInterpeter.h"

void toUpper(std::string &str) {
    int len = str.length();
    for (int i = 0; i < len; ++i) {
        str[i] = toupper(str[i]);
    }
}

bool deleteConfirmation() {
    char ch;
    std::cout << "Do you wish to remove this item? Please select [y/n]!\n";
    std::cin >> ch;

    return toupper(ch) == 'Y';
}

CommandInterpreter::CommandInterpreter(std::vector<Registration *> &regs,
                                       std::vector<Vehicle *> &vehicles,
                                       std::vector<Person *> &people) {
    this->vehicles = &vehicles;
    this->people = &people;
    this->regs = &regs;
}

void CommandInterpreter::interpret(std::string commandLine) {
    if(commandLine.length() == 0){
        throw std::invalid_argument("Empty command line!");
    }

    std::vector<std::string> commandParts;
    size_t pos = 0;
    size_t quotePos = 0;
    std::string token;

    while (true) {
        pos = commandLine.find(' ');
        quotePos = commandLine.find("\"");

        if (pos != std::string::npos) {
            if (quotePos > pos && quotePos != std::string::npos) {
                token = commandLine.substr(0, pos);
                commandParts.push_back(token);
                commandLine.erase(0, pos + 1);
            } else {
                if (quotePos != std::string::npos) {
                    commandLine.erase(quotePos, quotePos + 1);

                    size_t tempQuotePos = commandLine.find("\"");
                    token = commandLine.substr(quotePos, tempQuotePos);

                    commandParts.push_back(token);
                    commandLine.erase(0, tempQuotePos + 1);
                } else {
                    token = commandLine.substr(0, pos);
                    removeWs(token);
                    if (token.length() > 0) {
                        commandParts.push_back(token);
                    }
                    commandLine.erase(0, pos + 1);
                }
            }
        } else {
            if (commandLine.length() > 0) {
                token = commandLine.substr(0, commandLine.length());
                commandParts.push_back(token);
            }

            break;
        }
    }
    removeWs(commandParts[0]); //remove all WS from first string because I need to compare it
    toUpper(commandParts[0]);

    try {
        route(commandParts);
    } catch (const std::invalid_argument &ia) {
        std::cout << ia.what() << "\n";
    }

}

void CommandInterpreter::removeWs(std::string &str) {
    if(str.length()){
        str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
    }
}

void CommandInterpreter::route(std::vector<std::string> &args) {

    if (args[0] == "VEHICLE") {
        createVehicle(args);
    } else if (args[0] == "PERSON") {
        createPerson(args);
    } else if (args[0] == "ACQUIRE") {
        acquire(args);
    } else if (args[0] == "RELEASE") {
        release(args);
    } else if (args[0] == "REMOVE") {
        remove(args);
    } else if (args[0] == "SAVE") {
        save(args);
        std::cout << "Saved!" << std::endl;
    } else if (args[0] == "SHOW") {
        show(args);
    } else {
        throw std::invalid_argument("Invalid argument!");
    }

}

void CommandInterpreter::createVehicle(const std::vector<std::string> &args) {
    if (args.size() != 3) { //VEHICLE <registration> <description>
        throw std::invalid_argument("Wrong function format!");
    }

    Registration *reg = new Registration(args[1]);
    if (Registration::registrationExists(*reg, regs)) {
        delete reg; //now the registration is invalid and there is no need of this pointer
        throw std::invalid_argument("Registration already exists.");
    }

    Vehicle *vhcl = new Vehicle(reg, args[2]);

    regs->push_back(reg);
    vehicles->push_back(vhcl);

}

void CommandInterpreter::createPerson(const std::vector<std::string> &args) {
    unsigned id;
    if (args.size() != 3) { //PERSON <name> <id>
        throw std::invalid_argument("Wrong function format!");
    }

    id = strtoul(args[2].c_str(), nullptr, 0);
    if (Person::idExists(id, people)) {
        throw std::invalid_argument("Person is already born.");
    }

    Person *p = new Person(args[1], id);

    people->push_back(p);

}

void CommandInterpreter::acquire(const std::vector<std::string> &args) {
    if (args.size() != 3) { //ACQUIRE <owner-id> <vehicle-id>
        throw std::invalid_argument("Wrong function format!");
    }

    unsigned id = strtoul(args[1].c_str(), nullptr, 0);
    Vehicle *wantedVehicle = Vehicle::findById(args[2], vehicles);

    if (!wantedVehicle) {
        throw std::invalid_argument("Vehicle with this type of registration does not exist!");
    }

    Person *wantedPerson = Person::findById(id, people);
    if (!wantedPerson) {
        throw std::invalid_argument("Person does not exist!");
    }

    if (wantedVehicle->getOwner()) {
        Person *oldOwner = Person::findById(wantedVehicle->getOwner()->getId(), people);
        oldOwner->removeVehicle(wantedVehicle);
    }

    wantedPerson->addVehicle(wantedVehicle);
}

void CommandInterpreter::release(const std::vector<std::string> &args) {

    if (args.size() != 3) { //RELEASE <owner-id> <vehicle-id>
        throw std::invalid_argument("Wrong function format!");
    }

    unsigned id = strtoul(args[1].c_str(), nullptr, 0);
    Vehicle *wantedVehicle = Vehicle::findById(args[2], vehicles);

    if (!wantedVehicle) {
        throw std::invalid_argument("Vehicle with this type of registration does not exist!");
    }

    Person *wantedPerson = Person::findById(id, people);
    if (!wantedPerson) {
        throw std::invalid_argument("Person does not exist!");
    }

    wantedPerson->removeVehicle(wantedVehicle);
}

void CommandInterpreter::remove(const std::vector<std::string> &args) {
    if (args.size() != 2) {
        throw std::invalid_argument("Wrong function format!");
    }

    unsigned id;
    Vehicle *wantedVehicle;
    Person *wantedPerson;

    if (Registration::isNumberValid(args[1])) {
        wantedVehicle = Vehicle::findById(const_cast<std::string &>(args[1]), vehicles);
        if (wantedVehicle) {
            //confirmation
            if (deleteConfirmation()) {
                wantedVehicle->removeOwner();
                purge(wantedVehicle);
            }
        }
    }

    id = strtoul(args[1].c_str(), nullptr, 0);
    wantedPerson = Person::findById(id, people);
    if (wantedPerson) {
        //confirmation
        if (deleteConfirmation()) {
            purge(wantedPerson);
        }
    }
}

void CommandInterpreter::save(const std::vector<std::string> &args) {
    if (args.size() != 2) {
        throw std::invalid_argument("Wrong function format!");
    }

    std::ofstream savePath(args[1], std::ios::out | std::ios::trunc);

    if (savePath.good()) {

        size_t peopleLen = people->size();
        size_t vehicleLen = vehicles->size();

        for (int i = 0; i < peopleLen; ++i) {
            if (savePath.good()) {
                savePath << "PERSON ";

                if ((*people)[i]->getName().find(' ')) {
                    savePath << "\"" << (*people)[i]->getName() << "\"";
                } else {
                    savePath << (*people)[i]->getName();
                }

                savePath << " " << (*people)[i]->getId() << std::endl;
            }
        }

        for (int i = 0; i < vehicleLen; ++i) {
            if (savePath.good()) {
                savePath << "VEHICLE ";
                savePath << (*vehicles)[i]->getRegistration().getRegistrationNumber() << " ";

                if ((*vehicles)[i]->getDescription().find(' ')) {
                    savePath << "\"" << (*vehicles)[i]->getDescription() << "\"";
                } else {
                    savePath << (*vehicles)[i]->getDescription();
                }

                savePath << std::endl;
            }
        }

        for (int i = 0; i < vehicleLen; ++i) {
            if (savePath.good()) {
                if ((*vehicles)[i]->getOwner()) {
                    savePath << "ACQUIRE ";
                    savePath << (*vehicles)[i]->getOwner()->getId() << " ";
                    savePath << (*vehicles)[i]->getRegistration().getRegistrationNumber() << std::endl;
                }
            }
        }

        if (savePath.is_open()) {
            savePath.close();
        }

    } else {
        throw std::invalid_argument("Failed to open file!");
    }

}

// remove wantedVehicle from vehicles
void CommandInterpreter::purge(Vehicle *wantedVehicle) {
    std::size_t vhclsLen = vehicles->size();
    std::size_t regLen = regs->size();

    //remove vehicle
    for (int i = 0; i < vhclsLen; ++i) {
        if ((*vehicles)[i] == wantedVehicle) {
            vehicles->erase(this->vehicles->begin() + i);
        }
    }

    //remove registration
    for (int i = 0; i < regLen; ++i) {
        if (*(*regs)[i] == wantedVehicle->getRegistration()) {
            delete (*regs)[i];
            regs->erase(this->regs->begin() + i);
        }
    }

    delete wantedVehicle;
}

// remove wantedPerson from people
void CommandInterpreter::purge(Person *wantedPerson) {
    std::size_t len = people->size();
    std::size_t vhclsLen = wantedPerson->getVehicles().size();

    for (int i = 0; i < vhclsLen; ++i) {
        wantedPerson->removeVehicle(wantedPerson->getVehicles()[i]);
    }

    for (int i = 0; i < len; ++i) {
        if ((*people)[i] == wantedPerson) {
            delete wantedPerson;
            people->erase(this->people->begin() + i);
            break;
        }
    }
}

void CommandInterpreter::show(const std::vector<std::string> &args) {
    unsigned id;

    if (args.size() != 2) {
        throw std::invalid_argument("Wrong function format!");
    }

    if (args[1] == "PEOPLE") {
        showPeople();
    } else if (args[1] == "VEHICLES") {
        showVehicles();
    } else {
        id = strtoul(args[1].c_str(), nullptr, 0);

        //if is valid than print vehicle
        if (Registration::isNumberValid(args[1])) {
            showVehicle(args[1]);

        } else {
            if (id == 0 && args[1].length() != 1) { // strtoul returns 0 if the string is not a number
                throw std::invalid_argument("Id is not valid!");

            } else { //if id is valid
                showPerson(id);
            }
        }
    }

}

void CommandInterpreter::showVehicle(const std::string &id) const {
    Vehicle *wantedVehicle = Vehicle::findById(id, vehicles);

    if (wantedVehicle) {//wantedVehicle could be nullptr
        std::cout << *wantedVehicle;

        if (wantedVehicle->getOwner()) {
            std::cout << *(wantedVehicle->getOwner()) << std::endl;
        } else {
            std::cout << "Does not have owner." << std::endl;
        }
    } else {
        throw std::invalid_argument("No such vehicle found!");
    }
}

void CommandInterpreter::showVehicles() const {
    std::size_t len = vehicles->size();

    for (int i = 0; i < len; ++i) {
        std::cout << *(*vehicles)[i];

        if ((*vehicles)[i]->getOwner()) {
            std::cout << *(*vehicles)[i]->getOwner() << std::endl;
        } else {
            std::cout << "Does not have owner." << std::endl;
        }

    }
}

void CommandInterpreter::showPeople() const {
    std::size_t len = people->size();

    for (int i = 0; i < len; ++i) {
        std::cout << (*(*people)[i]) << std::endl;
        (*people)[i]->printCars();
    }
}

void CommandInterpreter::showPerson(const unsigned id) const {
    Person *wantedPerson = Person::findById(id, people);

    if (wantedPerson) {
        std::cout << *wantedPerson << std::endl;
        wantedPerson->printCars();
    } else {
        throw std::invalid_argument("Person not found!");
    }

}









