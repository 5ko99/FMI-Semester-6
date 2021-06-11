#include "../Headers/CommandParser.h"

#include <fstream>
#include <stdexcept>

using std::cout;
using std::endl;

CommandParser::~CommandParser() {
    for (int i = 0; i < this->vehicles.size(); ++i) {
        delete vehicles[i];
    }

    for (int i = 0; i < this->people.size(); ++i) {
        delete people[i];
    }
}

std::vector<Vehicle *> CommandParser::getVehicles() const {
    return this->vehicles;
}

std::vector<Person *> CommandParser::getPeople() const {
    return this->people;
}

void CommandParser::parseCommand(std::string &command) {
    try {
        std::vector<std::string> commands = this->split(command);

        if (commands[0] == "end") {
            return;
        }

        int personId = 0;

        if (commands[0] == "vehicle") {
            this->createVehicle(commands[1], commands[2]);

        } else if (commands[0] == "person") {
            try {
                personId = std::abs(std::stoi(commands[2]));
                this->createPerson(commands[1], personId);
            } catch (std::invalid_argument &exc) {
                cout << "Person's id must be a number!" << endl;
            }

        } else if (commands[0] == "acquire") {
            try {
                personId = std::abs(std::stoi(commands[1]));
                this->acquireVehicle(personId, commands[2]);
            } catch (std::invalid_argument &exc) {
                cout << "Person's id must be a number!" << endl;
            }

        } else if (commands[0] == "release") {
            try {
                personId = std::abs(std::stoi(commands[1]));
                this->releaseVehicle(personId, commands[2]);
            } catch (std::invalid_argument &exc) {
                cout << "Person's id must be a number!" << endl;
            }

        } else if (commands[0] == "remove") {
            if (isNumber(commands[1][0])) {
                try {
                    personId = std::abs(std::stoi(commands[1]));
                    this->removePerson(personId);
                } catch (std::invalid_argument &exc) {
                    cout << "Person's id must be a number!" << endl;
                }

            } else {
                this->removeVehicle(commands[1]);
            }

        } else if (commands[0] == "save") {
            this->saveData(commands[1]);

        } else if (commands[0] == "show") {
            if (isNumber(commands[1][0])) {
                try {
                    personId = std::abs(std::stoi(commands[1]));
                    this->printPerson(personId);
                } catch (std::invalid_argument &exc) {
                    cout << "Person's id must be a number!" << endl;
                }

            } else if (isNumber(commands[1][2])) {
                this->printVehicle(commands[1]);

            } else {
                this->toLower(commands[1]);
                this->printAll(commands[1]);
            }

        }
    } catch (std::invalid_argument &exc) {
        cout << exc.what() << endl;
    }
}

//-------------------

void CommandParser::createVehicle(const std::string &registration, const std::string &description) {
    try {
        validateRegistration(registration);
        int vehicleIndex = findVehicle(registration);

        Registration reg(registration);
        Vehicle *vehicle;

        if (vehicleIndex == -1) {
            vehicle = new Vehicle(reg, description);
            this->vehicles.push_back(vehicle);
        } else {
            cout << "Vehicle with this registration already exists" << endl;
        }
    } catch (std::invalid_argument &exc) {
        cout << exc.what() << endl;
    } catch (std::bad_alloc &exc) {
        cout << exc.what() << endl;
    }
}

void CommandParser::createPerson(const std::string &name, int id) {
    int personIndex = findPerson(id);
    Person *person;
    if (personIndex == -1) {
        try {
            person = new Person(name, id);
            this->people.push_back(person);
        } catch (std::bad_alloc &exc) {
            cout << exc.what() << endl;
        }
    } else {
        cout << "Person with this id already exists" << endl;
    }
}

void CommandParser::acquireVehicle(int personId, const std::string &registration) {
    int personIndex = findPerson(personId);
    int vehicleIndex = findVehicle(registration);

    if (personIndex == -1) {
        cout << "Person doesn't exists" << endl;
    } else if (vehicleIndex == -1) {
        cout << "Vehicle doesn't exists" << endl;
    } else {
        this->vehicles[vehicleIndex]->setOwner(*this->people[personIndex]);
    }
}

void CommandParser::releaseVehicle(int personId, const std::string &registration) {
    int personIndex = findPerson(personId);
    int vehicleIndex = findVehicle(registration);

    if (personIndex == -1) {
        cout << "Person doesn't exists" << endl;
    } else if (vehicleIndex == -1) {
        cout << "Vehicle doesn't exists" << endl;
    } else if (this->vehicles[vehicleIndex]->getOwner() == nullptr) {
        cout << "This vehicle doesn't have an owner!" << endl;
    } else if (this->vehicles[vehicleIndex]->getOwner()->getId() != personId) {
        cout << "This vehicle belongs to someone else!" << endl;
    } else {
        this->vehicles[vehicleIndex]->removeOwner();
    }
}

void CommandParser::removePerson(int personId) {
    int personIndex = findPerson(personId);
    std::string confirmation = "yes";

    if (personIndex != -1) {
        if (!this->people[personIndex]->getVehicles().empty()) {
            cout << "This person has " << this->people[personIndex]->getVehicles().size()
                 << " vehicles! Proceed with removing? Type (yes/no)!" << std::endl;

            std::cin >> confirmation;
            std::cin.ignore();
            this->toLower(confirmation);
        }

        if (confirmation == "yes") {
            try {
                while (!this->people[personIndex]->getVehicles().empty()) {
                    this->people[personIndex]->getVehicles().back()->removeOwner();
                }
            }
            catch (std::invalid_argument &exc) {
                cout << exc.what();
            }

            delete this->people[personIndex];
            this->people[personIndex] = this->people.back();
            this->people.pop_back();
        } else {
            cout << "Person wasn't removed" << endl;
        }
    } else {
        cout << "Person doesn't exists" << endl;
    }
}

void CommandParser::removeVehicle(const std::string &registration) {
    int vehicleIndex = findVehicle(registration);
    std::string confirmation = "yes";

    if (vehicleIndex != -1) {

        if (this->vehicles[vehicleIndex]->getOwner() != nullptr) {
            cout << "This vehicle has an owner! Proceed with removing? Type (yes/no)!" << std::endl;

            std::cin >> confirmation;
            std::cin.ignore();
            this->toLower(confirmation);
        }

        if (confirmation == "yes") {
            try {
                this->vehicles[vehicleIndex]->removeOwner();
            }
            catch (std::invalid_argument &exc) {
                cout << exc.what();
            }

            delete this->vehicles[vehicleIndex];
            this->vehicles[vehicleIndex] = this->vehicles.back();
            this->vehicles.pop_back();
        } else {
            cout << "Vehicle wasn't removed" << endl;
        }
    } else {
        cout << "Vehicle doesn't exists" << endl;
    }
}

void CommandParser::saveData(std::string &path) {
    std::fstream file;
    std::string confirmation = "yes";
    file.open(path);

    if (file.good()) {
        cout << "This file already exist! Do you want to overwrite it? Type (yes/no)!" << endl;
        std::cin >> confirmation;
        std::cin.ignore();
        file.close();
    }

    if (confirmation == "yes") {
        this->saveHelper(path);
    } else {
        std::cout << "Data wasn't saved!" << endl;
    }
}

void CommandParser::saveHelper(const std::string &path) {
    std::ofstream osFile(path, std::ios::trunc);

    if (osFile.is_open()) {
        for (int i = 0; i < this->people.size(); ++i) {
            osFile << "Person ";

            if (this->people[i]->getName().find(' ') != std::string::npos) {
                osFile << '"' << this->people[i]->getName() << '"';
            } else {
                osFile << this->people[i]->getName();
            }
            osFile << " " << this->people[i]->getId() << std::endl;
        }

        for (int i = 0; i < this->vehicles.size(); ++i) {
            osFile << "Vehicle " << this->vehicles[i]->getRegistration() << " ";
            if (this->vehicles[i]->getDescription().find(' ') != std::string::npos) {
                osFile << '"' << this->vehicles[i]->getDescription() << '"' << std::endl;
            } else {
                osFile << this->vehicles[i]->getDescription() << std::endl;
            }
            if (this->vehicles[i]->getOwner() != nullptr) {
                osFile << "Acquire " << this->vehicles[i]->getOwner()->getId() << " "
                       << this->vehicles[i]->getRegistration() << std::endl;
            }
        }

        osFile.close();
    } else {
        cout << "File couldn't open!" << std::endl;
    }
}

void CommandParser::printPerson(int personId) {
    int personIndex = findPerson(personId);

    if (personIndex != -1) {
        cout << *this->people[personIndex];
    } else {
        cout << "Person doesn't exists" << endl;
    }
}

void CommandParser::printVehicle(const std::string &registration) {
    int vehicleIndex = findVehicle(registration);

    if (vehicleIndex != -1) {
        cout << *this->vehicles[vehicleIndex];
    } else {
        cout << "Vehicle doesn't exists" << endl;
    }
}

void CommandParser::printAll(const std::string &command) {
    if (command == "people") {
        for (int i = 0; i < this->people.size(); ++i) {
            cout << *this->people[i];
        }
        if (this->people.empty()) {
            cout << "There is no one!" << std::endl;
        }

    } else if (command == "vehicles") {
        for (int i = 0; i < this->vehicles.size(); ++i) {
            cout << *this->vehicles[i];
        }

        if (this->vehicles.empty()) {
            cout << "There aren't any vehicles!" << std::endl;
        }

    } else {
        cout << "Invalid command!" << endl;
    }
}

//------------------

std::vector<std::string> CommandParser::split(std::string &command) {
    std::vector<std::string> cmdSplit;

    bool flag = false;

    int currIndex = 0;
    int lastIndex = 0;
    int commandSize = command.size();

    while (currIndex != std::string::npos) {
        while (command[lastIndex] == ' ') {
            lastIndex++;
        }

        if (lastIndex == commandSize) {
            break;
        }

        if (command[lastIndex] == '"') {
            flag = true;
        }

        if (!flag) {
            currIndex = command.find(' ', lastIndex);
            cmdSplit.push_back(command.substr(lastIndex, currIndex - lastIndex));
            lastIndex = currIndex;
        } else {
            currIndex = command.find('"', lastIndex + 1);
            cmdSplit.push_back(command.substr(lastIndex + 1, currIndex - lastIndex - 1));
            flag = false;
            lastIndex = currIndex + 1;
        }
    }

    this->toLower(cmdSplit[0]);

    validateCommand(cmdSplit);

    return cmdSplit;
}

int CommandParser::findVehicle(const std::string &registration) const {
    for (int i = 0; i < this->vehicles.size(); ++i) {
        if (this->vehicles[i]->getRegistration() == registration) {
            return i;
        }
    }

    return -1;
}

int CommandParser::findPerson(const unsigned int id) {
    for (int i = 0; i < this->people.size(); ++i) {
        if (this->people[i]->getId() == id) {
            return i;
        }
    }

    return -1;
}

void CommandParser::toLower(std::string &command) {
    const int letterDiff = 'a' - 'A';

    for (int i = 0; i < command.size(); ++i) {
        if (command[i] >= 'A' && command[i] <= 'Z') {
            command[i] += letterDiff;
        }
    }
}

void CommandParser::validateCommand(const std::vector<std::string> &commands) const {
    int cmdSize = commands.size();
    bool validCmdLong =
            (commands[0] == "vehicle" || commands[0] == "person"
             || commands[0] == "acquire" || commands[0] == "release");

    bool validCmdShort =
            (commands[0] == "remove" || commands[0] == "save" || commands[0] == "show" || commands[0] == "end");

    if (!validCmdLong && !validCmdShort) {
        throw std::invalid_argument("Command with such a name doesn't exists!");
    }

    if (validCmdShort && commands[0] != "end") {
        if (cmdSize > 2) {
            throw std::invalid_argument("Incorrect command! Too many arguments!");
        }

        if (cmdSize < 2) {
            throw std::invalid_argument("Incorrect command! Not enough arguments!");
        }
    } else if (validCmdLong) {
        if (cmdSize > 3) {
            throw std::invalid_argument("Incorrect command! Too many arguments!");
        }

        if (cmdSize < 3) {
            throw std::invalid_argument("Incorrect command! Not enough arguments!");
        }
    }
}

void CommandParser::validateRegistration(const std::string &registration) {
    int from;
    if (registration.size() > 8 || registration.size() < 7) {
        throw std::invalid_argument("Invalid registration!");
    }

    from = (registration.size() == 8 ? 2 : 1);

    for (int i = 0; i < from; ++i) {
        if (!isCapLetter(registration[i])) {
            throw std::invalid_argument("Invalid registration!");
        }
    }

    for (int i = from; i < from + 4; ++i) {
        if (!isNumber(registration[i])) {
            throw std::invalid_argument("Invalid registration!");
        }
    }

    from += 4;
    for (int i = from; i < from + 2; ++i) {
        if (!isCapLetter(registration[i])) {
            throw std::invalid_argument("Invalid registration!");
        }
    }

}

bool CommandParser::isCapLetter(const char &symbol) const {
    return (symbol >= 'A' && symbol <= 'Z');
}

bool CommandParser::isNumber(const char &symbol) const {
    return (symbol >= '0' && symbol <= '9');
}
