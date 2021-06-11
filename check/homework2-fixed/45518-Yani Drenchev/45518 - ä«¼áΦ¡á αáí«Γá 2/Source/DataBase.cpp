//
// Created by Yani Drenchev on 10.05.21.
//

#include "../Headers/DataBase.h"

bool DataBase::executeCommand(Command &cmd, const std::string &commandString) {
    std::string registration, desc, name;
    unsigned int idPerson;
    switch (cmd.first) {
        case CommandCode::VEHICLE:
            if (!Registration::checkRegistration(cmd.second[0])) {
                std::cout << "Invalid registration number \n";
                return false;
            }
            if (!addVehicle(cmd.second[0], cmd.second[1])) {
                return false;
            }
            addCommand(commandString);
            break;
        case CommandCode::PERSON:
            try {
                idPerson = stoi(cmd.second[1]);
            }
            catch (std::invalid_argument &exx) {
                std::cout << "Invalid ID - must be numeric \n";
                return false;
            }
            if (!addPerson(cmd.second[0], idPerson)) {
                return false;
            }
            addCommand(commandString);
            break;
        case CommandCode::ACQUIRE:
            if (!Registration::checkRegistration(cmd.second[0])) {
                std::cout << "Invalid registration number \n";
                return false;
            }
            try {
                idPerson = stoi(cmd.second[1]);
            }
            catch (std::invalid_argument &exx) {
                std::cout << "Invalid ID - must be numeric \n";
                return false;
            }
            if (!acquire(cmd.second[0], idPerson)) {
                return false;
            }
            addCommand(commandString);
            break;
        case CommandCode::RELEASE:
            if (!Registration::checkRegistration(cmd.second[1])) {
                std::cout << "Invalid registration number \n";
                return false;
            }
            try {
                idPerson = stoi(cmd.second[0]);
            }
            catch (std::invalid_argument &exx) {
                std::cout << "Invalid ID - must be numeric \n";
                return false;
            }
            if (!release(cmd.second[1], idPerson)) {
                return false;
            }
            addCommand(commandString);
            break;
        case CommandCode::REMOVE:
            if (isnumber(cmd.second[0][0])) {
                idPerson = stoi(cmd.second[0]);
                if (removePerson(idPerson)) {
                    std::cout << "Person removed" << "\n";
                } else {
                    return false;
                }
            } else {
                if (!Registration::checkRegistration(cmd.second[0])) {
                    std::cout << "Invalid registration number \n";
                    return false;
                }
                if (removeVehicle(cmd.second[0])) {
                    std::cout << "Vehicle removed\n";
                } else {
                    return false;
                }
            }

            addCommand(commandString);
            break;
        case CommandCode::SAVE:
            return extractToFile(cmd.second[0]);
        case CommandCode::SHOW:
            show(cmd.second[0]);
            break;
    };
    return true;
}

bool DataBase::extractToFile(const std::string &path) {

    std::ofstream file;
    file.open(path);
    std::string answer;
    if (file.good()) {
        std::cout << "The file already exits, do you want to overwrite it? y/n \n";
        std::cin >> answer;
        if (answer == "n") {
            std::cout << "Aborting command \n";
            return false;
        }
    }
    std::cout << path;
    if (file.is_open()) {
        for (auto &command : commands) {
            file << command << "\n";
        }
        file.close();
        std::cout << "\n File is saved \n";
        return true;
    } else {
        std::cout << "Could not open file \n";
        return false;
    }
}


bool DataBase::acquire(const std::string &registration, unsigned int id) {
    Person *p;
    Vehicle *veh;
    p = findPerson(id);
    veh = findVehicle(registration);
    if (veh == nullptr) {
        return false;
    }
    if (veh->getPerson() != 0) {
        findPerson(veh->getPerson())->removeVehicle(registration);
        veh->setPerson(p->getId());
        p->addVehicle(veh->getRegistration());
        return true;
    }
    if (p == nullptr) {
        std::cout << "No such person - wrong ID \n";
        return false;
    }
    p->addVehicle(veh->getRegistration());
    veh->setPerson(p->getId());
    return true;
}

bool DataBase::addCommand(const std::string &cmd) {
    try {
        commands.push_back(cmd);
    } catch (std::bad_alloc &exx) {
        return false;
    }
    return true;
}

bool DataBase::addPerson(const std::string &name, unsigned int id) {
    if (findPerson(id) != nullptr) {
        std::cout << "Duplicated id" << "\n";
        return false;
    }
    try {
        people.emplace_back(name, id);
        return true;
    } catch (std::bad_alloc &ex) {
        std::cout << "No more memory \n";
    }

    return true;
}

bool DataBase::addVehicle(const std::string &registration, const std::string &desc) {
    if (findVehicle(registration) != nullptr) {
        std::cout << "Duplicated reg number";
        return false;
    }
    try {
        vehicles.emplace_back(registration, desc);
        return true;
    } catch (std::exception &exx) {
        std::cout << exx.what() << "\n";
    }
    return true;
}

bool DataBase::release(const std::string &registration, unsigned int id) {
    Person *p;
    Vehicle *veh;
    p = findPerson(id);
    veh = findVehicle(registration);
    if (p == nullptr) {
        std::cout << "No such person - wrong ID \n";
        return false;
    }
    if (veh == nullptr) {
        std::cout << "No such car - wrong registration \n";
        return false;
    }
    if (veh->getPerson() == 0) {
        std::cout << "This car does not has an owner \n";
        return false;
    }
    if (veh->getPerson() != p->getId()) {
        std::cout << "This car does not belong to this person \n";
        return false;
    }
    veh->setPerson(0);
    p->removeVehicle(veh->getRegistration());
    return true;
}

Vehicle *DataBase::findVehicle(const std::string &reg) {
    std::string testString = reg;
    testString.erase(testString.erase(remove(testString.begin(), testString.end(), ' '), testString.end()));
    for (auto &i : vehicles) {
        if (i.getRegistration() == testString)
            return &i;
    }
    return nullptr;
}

Person *DataBase::findPerson(unsigned int id) {
    for (auto &i : people) {
        if (i.getId() == id)
            return &i;
    }
    return nullptr;
}


void DataBase::printPeople() {
    std::cout << "Printing people" << "\n";
    for (auto &i : people) {
        i.print();
    }
}

void DataBase::printVehicles() {
    std::cout << "Printing vehicles" << "\n";
    for (auto &i : vehicles) {
        i.print();
    }
}

void DataBase::show(const std::string &argument) {

    std::string upperCase = argument;
    for (std::string::size_type i = 0; i < argument.size(); ++i) {
        upperCase[i] = toupper(argument[i]);
    }
    if (upperCase == "VEHICLES") {
        if (vehicles.empty()) {
            std::cout << "Nothing to print\n";
            return;
        }
        printVehicles();
    } else if (upperCase == "PEOPLE") {
        if (people.empty()) {
            std::cout << "Nothing to print\n";
            return;
        }
        printPeople();
    } else {
        Person *p;
        Vehicle *veh;
        unsigned int id;
        if (isnumber(argument[0])) {
            try {
                id = stoi(argument);
            } catch (std::invalid_argument &exx) {
                std::cout << "Invalid id or registration \n";
            }
            p = findPerson(id);
            if (p != nullptr) {
                std::vector<Registration> cars = p->getVehicles();
                if (cars.empty()) {
                    std::cout << "Nothing to print\n";
                    return;
                }
                std::cout << "Printing cars for: " << p->getName() << "\n";
                for (auto &car : cars) {
                    findVehicle(car.getRegistration())->print();
                }
            } else {
                std::cout << "No such person invalid id\n";
            }
            return;
        }
        if (Registration::checkRegistration(argument)) {
            veh = findVehicle(argument);
            if (veh == nullptr) {
                std::cout << "No such car invalid registration \n";
                return;
            }
            veh->print();
        } else {
            std::cout << "Invalid registration \n";
        }
    }
}


bool DataBase::importFromFile(const std::string &path) {
    std::ifstream file;
    file.open(path);
    std::string command;
    if (file.is_open()) {
        int line = 1;
        while (getline(file, command)) {
            auto x = parseCommand(command);
            bool isSuccess = DataBase::get_instance().executeCommand(x, command);
            if (!isSuccess) {
                std::cout << "Invalid command on line: " << line << "\n";
            }
            line++;
        }
        std::cout << "Commands imported \n";
    } else {
        std::cout << "Could not open file \n";
    }
    file.close();
    return false;
}

bool DataBase::removeVehicle(const std::string &vehicle) {
    std::vector<Vehicle>::iterator nth;
    Vehicle *veh = nullptr;
    for (int i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i].getRegistration() == vehicle) {
            veh = &vehicles[i];
            nth = vehicles.begin() + i;
        }
    }
    if (veh == nullptr) {
        std::cout << "Invalid registration no such vehicle\n";
        return false;
    }

    Person *per;
    std::string answer;
    if (veh->getPerson() != 0) {
        std::cout << "This vehicle has owner are you sure you want to remove it? \n"
                     "type y/n \n";
        getline(std::cin, answer);
        if (answer == "y") {
            per = findPerson(veh->getPerson());
            per->removeVehicle(vehicle);
            vehicles.erase(nth);
        } else {
            std::cout << "Aborting command \n";
            return false;
        }
    }else{
        vehicles.erase(nth);
    }
    return true;
}

bool DataBase::removePerson(unsigned int id) {
    std::vector<Person>::iterator personIt;
    Person *per = nullptr;
    std::string answer;
    for (int i = 0; i < people.size(); ++i) {
        if (people[i].getId() == id) {
            per = &people[i];
            personIt = people.begin() + i;
        }
    }
    if (per == nullptr){
        std::cout << "No such person invalid id \n";
        return false;
    }
    std::vector<Registration> personVeh = per->getVehicles();
    if (!personVeh.empty()) {
        std::cout << "This person has vehicles are you sure you want to remove it? \n"
                     "type y/n \n";
        getline(std::cin, answer);

        if (answer == "y") {
            for (auto &i : personVeh) {
                findVehicle(i.getRegistration())->setPerson(0);
            }
            people.erase(personIt);
        } else {
            std::cout << "Aborting command \n";
            return false;
        }
    }else{
        people.erase(personIt);
    }
    return true;
}
