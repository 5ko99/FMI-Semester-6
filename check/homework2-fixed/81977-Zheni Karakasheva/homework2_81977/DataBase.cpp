#include <vector>
#include <fstream>
#include "DataBase.h"

void DataBase::toUpperCase(std::string& command) {
    for (std::size_t i = 0; i < command.length(); i++) {
        command[i] = toupper(command[i]); //capitalizes each letter in the command
    }
}

//checks for a white space in command and removes it
void DataBase::removeWhiteSpaces(std::string& command) {
    for(int i = 0; i <= command.length(); i++) {
            for(int j = 0; j <= i; j++) {
                if(command[i] == ' ' && command[i+1] == ' ') { 
                    command.erase(command.begin() + i);
                } else if(command[0]== ' ') {
                    command.erase(command.begin()); 
                } else if(command[i] == '\0' && command[i-1]== ' ') {
                    command.erase(command.end() - 1);
            }
        }
    }
}

//displays a message if the user is sure about their choice and sets a flag for the decision
bool DataBase::confirmDeleting() {
    char choice;
    std::cout<<"Are you sure you want to delete this object? Input 'Y' for yes and any other letter for no:\n$ ";
    
    std::cin>>choice;

    return toupper(choice) == 'Y';
}

void DataBase::countArguments(const std::vector<std::string>& arguments, std::size_t neededCount) {
    if (arguments.size() != neededCount) {
        throw std::invalid_argument("The command you entered is not in the valid format!");
    }
}

void DataBase::vehicleCommand(const std::vector<std::string>& arguments) {
    countArguments(arguments,3); //check for the right amount of arguments

    std::string temp = arguments[1].c_str(); //a momentary temp for the registration number
    
    //if there exists an identical registration number, we cannot add the vehicle to the database
    for(std::size_t i = 0; i < registrations.size(); i++) {
        if (registrations[i]->getRegNumber() == temp) {
            throw std::invalid_argument("Cannot add this vehicle to the database!");
            temp.clear();

            break; 
        }
    }

    //if everything is okay - we have a new registration number and a new vehicle
    //which are added to the vectors of registrations and vehicles
    Registration* registrationTemp = new Registration(arguments[1].c_str());
    Vehicle* vehicleTemp = new Vehicle(registrationTemp, arguments[2]);

    registrations.push_back(registrationTemp);
    vehicles.push_back(vehicleTemp);

    std::cout<<"Successfully added!"<<std::endl;
}


void DataBase::personCommand(const std::vector<std::string>& arguments) {
    unsigned IDTemp;
    countArguments(arguments,3); //check for the right amount of arguments

    //if the person's ID already exists, we cannot add them to the database
    IDTemp = strtoul(arguments[2].c_str(), nullptr, 0);
    if (IDExists(IDTemp, people)) {
       throw std::invalid_argument("Cannot add this person to the database!");
    }

    //if everything is okay - we have a new person(personTemp) with IDTemp who is added to the vector of the people
    Person* personTemp = new Person(arguments[1].c_str(),IDTemp);
    people.push_back(personTemp);

    std::cout<<"Successfully added!"<<std::endl;
}

void DataBase::acquireCommand(const std::vector<std::string>& arguments) {
    countArguments(arguments,3); //check for the right amount of arguments

    unsigned IDTemp = strtoul(arguments[1].c_str(), nullptr, 0);

    //a necessary check for the existence of the vehicle
    Vehicle* vehicleToAcquire = findVehicleID(arguments[2],vehicles);
    if (!vehicleToAcquire) {
        throw std::invalid_argument("This vehicle does not exist in our database!");
    }

    //a necessary check for the existence of the person
    Person* personToAcquire = findPersonID(IDTemp, people);
    if (!personToAcquire) {
        throw std::invalid_argument("This person does not exist in our database!");
    }
  
    //if the vehichle has an owner - we find them
    //and then they are removed as an owner
    if (vehicleToAcquire->getOwner()) {
        Person* previousOwner = findPersonID(vehicleToAcquire->getOwner()->getID(), people);
        previousOwner->removeVehicleOwnership(vehicleToAcquire);
    }

    //the vehicle is added to the vector of owned vehicles of the person who has to acquire it
    personToAcquire->addVehicleOwnership(vehicleToAcquire);

    std::cout<<"Successfully acquired!"<<std::endl;
}

void DataBase::releaseCommand(const std::vector<std::string>& arguments) {
    countArguments(arguments,3); //check for the right amount of arguments

    unsigned IDTemp = strtoul(arguments[1].c_str(), nullptr, 0);

    //a necessary check for the existence of the vehicle
    Vehicle* vehicleToRelease = findVehicleID(arguments[2], vehicles);
    if (!vehicleToRelease) {
        throw std::invalid_argument("This vehicle does not exist in our database!");
    }

    //a necessary check for the existence of the person
    Person* personToRelease = findPersonID(IDTemp, people);
    if (!personToRelease) {
        throw std::invalid_argument("This person does not exist in our database!");
    }

    //if everything is okay - the person who has to be released of the ownership
    //is made no longer an owner of the vehicle
    personToRelease->removeVehicleOwnership(vehicleToRelease);

    std::cout<<"Successfully released!"<<std::endl;
}

void DataBase::removeCommand(const std::vector<std::string>& arguments) {
    countArguments(arguments,2); //check for the right amount of arguments

    unsigned IDTemp = strtoul(arguments[1].c_str(), nullptr, 0);
     
    Vehicle* vehicleToRemove;
    Person* personToRemove;

    //if the given registration number is valid we find the vehicle to be removed
    if (isValid(arguments[1].c_str()) ) {
        vehicleToRemove = findVehicleID(arguments[1], vehicles);

        //if there is a confirmation for the deletion the vehicle is removed both from ownership
        //and from the vector of the vehicles
        if (vehicleToRemove && confirmDeleting() ) {
            vehicleToRemove->removeOwnership();
            removeVehicle(vehicleToRemove);
        }
    }

    //if the argument is a valid person who exists in the vector of people
    //if there is a confirmation for the deletion the person is removed from the vector of people
    personToRemove = findPersonID(IDTemp, people);
    if (personToRemove && confirmDeleting() ) {
        removePerson(personToRemove);
    }

}

void DataBase::removeVehicle(Vehicle* vehicleToDelete) {
    //if the vehicle is found, it is deleted from the vector of the vehicles
    for (std::size_t i = 0; i < vehicles.size();i++) {
        if (vehicles[i] == vehicleToDelete) {
            vehicles.erase(vehicles.begin() + i);
        }
    }

    //if the registration number is found, it is deleted from the vector of the registration numbers
    for (std::size_t i = 0; i < registrations.size();i++) {
        if (registrations[i]->getRegNumber() == vehicleToDelete->getRegistration().getRegNumber()) {
            delete (registrations)[i];
            registrations.erase(registrations.begin() + i);
        }
    }

    delete vehicleToDelete; //the vehicle is deleted as a whole object

    std::cout<<"Successfully removed vehicle!"<<std::endl;
}

void DataBase::removePerson(Person* personToDelete) {
    //each vehicle the person owns is released from their ownership
    for (std::size_t i = 0; i < personToDelete->getOwnedVehicles().size(); i++) {
        personToDelete->removeVehicleOwnership(personToDelete-> getOwnedVehicles()[i] );
    }

    //if the person who has to be removed is found, they are deleted both as an object and from the vector
    //of people
    for (std::size_t i = 0; i < people.size();i++) {
        if (people[i] == personToDelete) {
            delete personToDelete;
            people.erase(people.begin() + i);

            break;
        }
    }

    std::cout<<"Successfully removed person!"<<std::endl;
}

void DataBase::saveCommand(const std::vector<std::string>& arguments) {
    countArguments(arguments,2); //check for the right amount of arguments

    std::ofstream pathToSave(arguments[1], std::ios::out | std::ios::trunc); //the place where the info
    //would be stored

    //if the path is correct
    if (pathToSave.good() ) {
        //the way the people would be stored
        for (std::size_t i = 0; i < people.size();i++) {
            if (pathToSave.good()) {
                pathToSave<<"PERSON ";
                if (people[i]->getName().find(' '))  {
                    pathToSave<<" "<<people[i]->getName()<<" ";
                } else {
                    pathToSave<<people[i]->getName();
                }
                pathToSave<<" "<< people[i]->getID()<<std::endl;
            }
        }

        //the way the vehicles would be stored
        for (std::size_t i = 0; i < vehicles.size();i++) {
            if (pathToSave.good()) {
                pathToSave<<"VEHICLE ";
                pathToSave<<(vehicles)[i]->getRegistration().getRegNumber()<<" ";

                if ((vehicles)[i]->getDescription().find(' ')) {
                    pathToSave<<" "<<(vehicles)[i]->getDescription()<<" ";
                } else {
                    pathToSave<<(vehicles)[i]->getDescription();
                }
                pathToSave<<std::endl;
            }
        }

        //the way "acquire" would be stored
        for (std::size_t i = 0; i < vehicles.size();i++) {
            if (pathToSave.good()) {
                if ((vehicles)[i]->getOwner()) {
                    pathToSave<<"ACQUIRE ";
                    pathToSave<<(vehicles)[i]->getOwner()->getID()<<" ";
                    pathToSave<<(vehicles)[i]->getRegistration().getRegNumber()<<std::endl;
                }
            }
        }

        //if the file is open, it would be closed
        if (pathToSave.is_open()) {
            pathToSave.close();
        }

        std::cout<<"The changes were successfully saved!"<<std::endl;
    } else {
        throw std::invalid_argument("The file could not be opened!"); //a message if the file is not correct
    }
}

void DataBase::showCommand(const std::vector<std::string>& arguments) {
    unsigned IDTemp;

    countArguments(arguments,2); //a check for enough arguments

    if (arguments[1] == "PEOPLE") {
        showPeople();
    } else if (arguments[1] == "VEHICLES") {
        showVehicles();
    } else {
        IDTemp = strtoul(arguments[1].c_str(), nullptr, 0);

        if(findPersonID(IDTemp, people) != nullptr) {
            showPerson(IDTemp);
        } else if (isValid(arguments[1].c_str())) {
            showVehicle(arguments[1]);
        } else { 
            throw std::invalid_argument("Invalid arguments!");
        }
    }
}

void DataBase::showVehicle(const std::string& searchedID) const {
    Vehicle* vehicleToShow = findVehicleID(searchedID, vehicles);

    if (vehicleToShow) {
        std::cout<<*vehicleToShow;

        if(vehicleToShow->getOwner()) {
            std::cout<<vehicleToShow->getOwner()<<std::endl;
        } else {
            std::cout<<"The vehicle does not have an owner"<<std::endl;
        }
    } else {
        throw std::invalid_argument("The vehicle does not exist in our database!");
    }
}

void DataBase::showVehicles() const {
    for (std::size_t i = 0; i < vehicles.size(); i++) {
        std::cout<<*vehicles[i];

        if (vehicles[i]->getOwner()) {
            std::cout<<*vehicles[i]->getOwner()<<std::endl;
        } else {
            std::cout<<"The vehicle does not have an owner"<<std::endl;
        }
    }
}

void DataBase::showPeople() const {
    for (std::size_t i = 0; i < people.size(); i++) {
        std::cout<<*people[i]<<std::endl;
    }
}

void DataBase::showPerson(const unsigned searchedID) const {
    Person* personToShow = findPersonID(searchedID, people);

    if (personToShow) {
        std::cout<<*personToShow<<std::endl;
    } else {
        throw std::invalid_argument("This person does not exist in our database!");
    }
}

//executes a command depending on the first argument
void DataBase::executeCommand(std::vector<std::string>& arguments) {
    if (arguments[0] == "VEHICLE") {
        vehicleCommand(arguments);
    } else if (arguments[0] == "PERSON") {
        personCommand(arguments);
    } else if (arguments[0] == "ACQUIRE") {
        acquireCommand(arguments);
    } else if (arguments[0] == "RELEASE") {
        releaseCommand(arguments);
    } else if (arguments[0] == "REMOVE") {
        removeCommand(arguments);
    } else if (arguments[0] == "SAVE") {
        saveCommand(arguments);
    } else if (arguments[0] == "SHOW") {
        showCommand(arguments);
    } else {
        throw std::invalid_argument("Invalid choice!");
    }
}

//finds the person by given ID
Person* DataBase::findPersonID(unsigned int searchedID, std::vector<Person*> people) {
    for (std::size_t i = 0; i < people.size(); ++i) {
        if (people[i]->getID() == searchedID) { 
            return people[i]; 
        }
    }

    return nullptr;
}

bool DataBase::IDExists(unsigned int searchedID, std::vector<Person*> people) {
    return findPersonID(searchedID, people) != nullptr; //if the result is different from a nullptr - person exists
}

//return a vehicle by the ID(for the vehicle that is the registration number) and returns it if found
Vehicle* DataBase::findVehicleID(const std::string& searchedID, std::vector<Vehicle*> vehicles) {
    for (std::size_t i = 0; i < vehicles.size(); i++) {
        if (vehicles[i]->getRegistration().getRegNumber() == searchedID) {
            return vehicles[i];
        }
    }

    return nullptr;
}

void DataBase::run(std::string commandPrompt) {
    //if there are no commands, a message would be shown
    if(commandPrompt.length() == 0) {
        throw std::invalid_argument("You have not entered any commands!");
    }

    std::vector<std::string> commandParts; //the vector for parsing the commands

    std::size_t position = 0; //the current position
    std::size_t quoteBegin = 0; //the beginning of quotation marks

    std::string partToPush; //a part which has to be parsed

    //the parsing
    while (true) {
        position = commandPrompt.find(' ');
        quoteBegin = commandPrompt.find("\"");

        if (position != std::string::npos) {
            if (quoteBegin > position && quoteBegin != std::string::npos) {

                partToPush = commandPrompt.substr(0, position);
                commandParts.push_back(partToPush);

                commandPrompt.erase(0, position+1);
            } else {
                if (quoteBegin != std::string::npos) {

                    commandPrompt.erase(quoteBegin, quoteBegin+1);

                    std::size_t quoteBeginTemp = commandPrompt.find("\"");

                    partToPush = commandPrompt.substr(quoteBegin, quoteBeginTemp);
                    commandParts.push_back(partToPush);

                    commandPrompt.erase(0, quoteBeginTemp + 1);
                } else {
                    partToPush = commandPrompt.substr(0, position);

                    if (partToPush.length() > 0) {
                        commandParts.push_back(partToPush);
                    }
                    commandPrompt.erase(0, position + 1);
                }
            }
        } else {
            if (commandPrompt.length() > 0) {
                partToPush = commandPrompt.substr(0,commandPrompt.length());
                commandParts.push_back(partToPush);
            }

            break;
        }
    }

    removeWhiteSpaces(commandParts[0]);
    toUpperCase(commandParts[0]);

    //if the execution cannot be successful - an exception is thrown
    try {
        executeCommand(commandParts);
    } catch (const std::invalid_argument& invalidArgument) {
        std::cout<<invalidArgument.what()<<std::endl;
    }

}

//deletes the memory used for registrations, people and vehicles
DataBase::~DataBase() {
    for (std::size_t i = 0; i < registrations.size(); i++) {
        delete registrations[i];
    }

    for (std::size_t i = 0; i < people.size(); i++) {
        delete people[i];
    }

    for (std::size_t i = 0; i < vehicles.size(); i++) {
        delete vehicles[i];
    }
}












