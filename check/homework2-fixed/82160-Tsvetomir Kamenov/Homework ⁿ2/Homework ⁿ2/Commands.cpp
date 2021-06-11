#include "Commands.h"

#include <iostream>
#include <fstream>

std::size_t Commands::getCommandLength() const
{
    return command.length();
}

std::string Commands::isIDorRegistration()
{
    if(argument1[0] > 'A' && argument1[0] < 'Z')
        return "REGISTRATION";
    else
        return "ID";
}

bool Commands::commandIsVehicle() const
{
    std::size_t length = getCommandLength();
    if(length != cmdVehicleLength)
        return false;
    else {
        if(command[0] == 'V' || command[0] == 'v')
            ;
        else
            return false;

        if(command[1] == 'E' || command[1] == 'e')
            ;
        else
            return false;

        if(command[2] == 'H' || command[2] == 'h')
            ;
        else
            return false;

        if(command[3] == 'I' || command[3] == 'i')
            ;
        else
            return false;

        if(command[4] == 'C' || command[4] == 'c')
            ;
        else
            return false;

        if(command[5] == 'L' || command[5] == 'l')
            ;
        else
            return false;

        if(command[6] == 'E' || command[6] == 'e')
            ;
        else
            return false;

        return true;
    }
}

bool Commands::commandIsPerson() const
{
    std::size_t length = getCommandLength();
    if(length != cmdPersonLength)
        return false;
    else {
        if(command[0] == 'P' || command[0] == 'p')
            ;
        else
            return false;

        if(command[1] == 'E' || command[1] == 'e')
            ;
        else
            return false;

        if(command[2] == 'R' || command[2] == 'r')
            ;
        else
            return false;

        if(command[3] == 'S' || command[3] == 's')
            ;
        else
            return false;

        if(command[4] == 'O' || command[4] == 'o')
            ;
        else
            return false;

        if(command[5] == 'N' || command[5] == 'n')
            ;
        else
            return false;

        return true;
    }
}

bool Commands::commandIsAcquire() const
{
    std::size_t length = getCommandLength();
    if(length != cmdAcquireLength)
        return false;
    else {
        if(command[0] == 'A' || command[0] == 'a')
            ;
        else
            return false;

        if(command[1] == 'C' || command[1] == 'c')
            ;
        else
            return false;

        if(command[2] == 'Q' || command[2] == 'q')
            ;
        else
            return false;

        if(command[3] == 'U' || command[3] == 'u')
            ;
        else
            return false;

        if(command[4] == 'I' || command[4] == 'i')
            ;
        else
            return false;

        if(command[5] == 'R' || command[5] == 'r')
            ;
        else
            return false;

        if(command[6] == 'E' || command[6] == 'e')
            ;
        else return false;

        return true;

    }
}

bool Commands::commandIsRelease() const
{
    std::size_t length = getCommandLength();
    if(length != cmdReleaseLength)
        return false;
    else {
        if(command[0] == 'R' || command[0] == 'r')
            ;
        else
            return false;

        if(command[1] == 'E' || command[1] == 'e')
            ;
        else
            return false;

        if(command[2] == 'L' || command[2] == 'l')
            ;
        else
            return false;

        if(command[3] == 'E' || command[3] == 'e')
            ;
        else
            return false;

        if(command[4] == 'A' || command[4] == 'a')
            ;
        else
            return false;

        if(command[5] == 'S' || command[5] == 's')
            ;
        else
            return false;

        if(command[6] == 'E' || command[6] == 'e')
            ;
        else
            return false;

        return true;
    }
}

bool Commands::commandIsRemove() const
{
    std::size_t length = getCommandLength();
    if(length != cmdRemoveLength)
        return false;
    else {
        if(command[0] == 'R' || command[0] == 'r')
            ;
        else
            return false;

        if(command[1] == 'E' || command[1] == 'e')
            ;
        else
            return false;

        if(command[2] == 'M' || command[2] == 'm')
            ;
        else
            return false;

        if(command[3] == 'O' || command[3] == 'o')
            ;
        else
            return false;

        if(command[4] == 'V' || command[4] == 'v')
            ;
        else
            return false;

        if(command[5] == 'E' || command[5] == 'e')
            ;
        else
            return false;

        return true;
    }
}

bool Commands::commandIsSave() const
{
    std::size_t length = getCommandLength();
    if(length != cmdSaveLength)
        return false;
    else {
        if(command[0] == 'S' || command[0] == 's')
            ;
        else
            return false;

        if(command[1] == 'A' || command[1] == 'a')
            ;
        else
            return false;

        if(command[2] == 'V' || command[2] == 'v')
            ;
        else
            return false;

        if(command[3] == 'E' || command[3] == 'e')
            ;
        else
            return false;

        return true;
    }
}

bool Commands::commandIsShow() const
{
    std::size_t length = getCommandLength();
    if(length != cmdShowLength)
        return false;
    else {
        if(command[0] == 'S' || command[0] == 's')
            ;
        else
            return false;

        if(command[1] == 'H' || command[1] == 'h')
            ;
        else
            return false;

        if(command[2] == 'O' || command[2] == 'o')
            ;
        else
            return false;

        if(command[3] == 'W' || command[3] == 'w')
            ;
        else
            return false;

        return true;
    }
}

bool Commands::commandIsExit() const
{
    std::size_t length = getCommandLength();
    if(length != cmdExitLength)
        return false;
    else {
        if(command[0] == 'E' || command[0] == 'e')
            ;
        else
            return false;

        if(command[1] == 'X' || command[1] == 'x')
            ;
        else
            return false;

        if(command[2] == 'I' || command[2] == 'i')
            ;
        else
            return false;

        if(command[3] == 'T' || command[3] == 't')
            ;
        else
            return false;

        return true;
    }
}

std::string Commands::interpretCommand()
{
    std::size_t length = getCommandLength();

    if(length == cmdLength7) {
        if(commandIsVehicle())
            return "VEHICLE";
        else if(commandIsAcquire())
            return "ACQUIRE";
        else if(commandIsRelease())
            return "RELEASE";
        else
            return "UNKNOWN";
    }

    else if(length == cmdLength6) {
        if(commandIsPerson())
            return "PERSON";
        else if(commandIsRemove())
            return "REMOVE";
        else
            return "UNKNOWN";
    }

    else if(length == cmdLength4) {
        if(commandIsShow())
            return "SHOW";
        else if(commandIsSave())
            return "SAVE";
        else if(commandIsExit())
            return "EXIT";
        else
            return "UNKNOWN";
    }

    return "UNKNOWN";
}

void Commands::collectCommands()
{
    std::string cmd = interpretCommand();

    m_commands.push_back(command);
    m_commands.push_back(argument1);
    if(cmd == "PERSON" || cmd == "VEHICLE" || cmd == "ACQUIRE" || cmd == "RELEASE") {
        m_commands.push_back(argument2);
    }
    else if(cmd == "REMOVE") {
        m_commands.push_back("EMPTY");
    }
}

bool Commands::saveCommands()
{
    std::ofstream file(argument1, std::ios::app);
    if(!file) {
        std::cout << argument1 << " could not be opened!";
        return false;
    }
    std::size_t size = m_commands.size();
    for(std::size_t index = 0; index < size; ++index) {
        file << m_commands[index] << '\n';
    }

    file.close();
    return true;
}

void Commands::CommandCentre()
{
    std::string perform = interpretCommand();

    if(perform == "PERSON") {
        collectCommands();
        addPerson();
        return;
    }

    if(perform == "VEHICLE") {
        collectCommands();
        addVehicle();
        return;
    }

    if(perform == "ACQUIRE") {
        collectCommands();
        acquireVehicle();
        return;
    }

    if(perform == "RELEASE") {
        collectCommands();
        releaseVehicle();
        return;
    }

    if(perform == "REMOVE") {
        std::string choice = isIDorRegistration();

        if(choice == "REGISTRATION") {
            collectCommands();
            removeVehicle();
            return;
        }

        if(choice == "ID") {
            collectCommands();
            removePerson();
            return;
        }
    }

    if(perform == "SHOW") {
        if(argument1 == "PEOPLE") {
            showPeople();
            return;
        }

        else if(argument1 == "VEHICLES") {
            showVehicles();
            return;
        }

        else {
            std::string choice = isIDorRegistration();

            if(choice == "REGISTRATION") {
                showVehicleByReg();
                return;
            }

            if(choice == "ID") {
                showPersonByID();
                return;
            }
        }
    }

    if(perform == "SAVE") {
        if(saveCommands())
            std::cout << "Progress saved into " << argument1 << '\n';
        else
            std::cout << "Your progress could not be saved.\n";
    }

    if(perform == "EXIT") {
        exit = true;
        std::cout << "Thanks for using our application, see you soon!\n";
    }

    if(perform == "UNKNOWN")
        std::cout << "Unknown command!\n";
}

std::size_t Commands::getPeopleSize() const
{
    return m_people.size();
}

std::size_t Commands::getVehiclesSize() const
{
    return m_vehicles.size();
}

//this function is only called when the user wants
//to create a new object of type Vehicle
unsigned int Commands::convertStringToInt()
{
    unsigned int ID = std::stoi(argument2);

    return ID;
}

//this function is only called when the user wants
//to create a new object of type Vehicle
bool Commands::isValidReg()
{
    Registration temp_reg(argument1);

    if(temp_reg.isValidReg())
        return true;
    else
        return false;
}

//this function is only called when the user wants
//to create a new object of type Person
bool Commands::isUniqueID()
{
    std::size_t size = getPeopleSize();
    unsigned int ID = convertStringToInt();

    for(size_t index = 0; index < size; ++index) {
        if(ID == m_people[index].getID())
            return false;
    }

    return true;
}

//this function is only called when the user wants
//to create a new object of type Vehicle
bool Commands::isUniqueReg()
{
    std::size_t size = getVehiclesSize();
    Registration temp_reg(argument1);

    for(size_t index = 0; index < size; ++index) {
        if(temp_reg.getReg() == m_vehicles[index].getReg())
            return false;
    }

    return true;
}

void Commands::addVehicle()
{
    if(isValidReg() && isUniqueReg()) {
        m_vehicles.push_back(Vehicle(argument1, argument2));
        std::cout << "Vehicle added!\n";
    }
    else
        std::cout << "The registration is either already taken or not valid!\n";
}

void Commands::addPerson()
{
    unsigned int ID = convertStringToInt();

    if(isUniqueID()) {
        m_people.push_back(Person(argument1, ID));
        std::cout << "Person added!\n";
    }
    else
        std::cout << "There is a person with this ID already!\n";
}

//returns the index for the wanted Person object
//in the array, if there is no object with such ID
//returns -1
//used for acquire, release, remove and show person by ID commands
int Commands::searchForPersonIndex()
{
    unsigned int ID = std::stoi(argument1);
    std::size_t size = getPeopleSize();

    for(size_t index = 0; index < size; ++index) {
        if(ID == m_people[index].getID())
            return index;
    }

    return -1;
}

//returns the index for the wanted Vehicle object
//in the array, if there is no object with such ID
//returns -1
//used for acquire and release commands
int Commands::searchForVehicleIndex()
{
    Registration temp_reg(argument2);
    std::size_t size = getVehiclesSize();

    for(size_t index = 0; index < size; ++index) {
        if(temp_reg.getReg() == m_vehicles[index].getReg())
            return index;
    }

    return -1;
}

//returns the index for the wanted Vehicle object
//in the array, if there is no object with such ID
//returns -1
//used for remove and show vehicle by registration commands
int Commands::searchForVehicleIndex2()
{
    Registration temp_reg(argument1);
    std::size_t size = getVehiclesSize();

    for(size_t index = 0; index < size; ++index) {
        if(temp_reg.getReg() == m_vehicles[index].getReg())
            return index;
    }

    return -1;
}

void Commands::acquireVehicle()
{
    int personIndex = searchForPersonIndex();
    if(personIndex == -1) {
        std::cout << "There is no person with such ID.\n";
        return;
    }

    int vehicleIndex = searchForVehicleIndex();
    if(vehicleIndex == -1) {
        std::cout << "There is no vehicle with such registration.\n";
        return;
    }

    m_people[personIndex].acquireVehicle(m_vehicles[vehicleIndex]);
    std::cout << "Vehicle acquired!\n";
}

void Commands::releaseVehicle()
{
    int personIndex = searchForPersonIndex();
    if(personIndex == -1) {
        std::cout << "There is no person with such ID.\n";
        return;
    }

    int vehicleIndex = searchForVehicleIndex();
    if(vehicleIndex == -1) {
        std::cout << "There is no vehicle with such registration.\n";
        return;
    }

    m_people[personIndex].removeOwnedVehicle(m_vehicles[vehicleIndex]);
    std::cout << "Vehicle released!\n";
}

void Commands::removePerson()
{
    int index = searchForPersonIndex();
    if(m_people[index].ownsVehicles()) {
        m_people[index].outputVehicles();
        std::cout << "\n Are you sure you want to delete it? (y/n): ";
        char answer;
        std::cin >> answer;
        bool key;
        answer == 'y' || answer == 'Y' ? key = true : key = false;
        if(key) {
            m_people[index].removeAllVehicles();
            m_people.erase(m_people.begin()+index);
            std::size_t newSize = getPeopleSize();
            m_people.resize(newSize);
            std::cout << "Person removed!\n";
        }
    }
    else {
        m_people.erase(m_people.begin()+index);
        std::size_t newSize = getPeopleSize();
        m_people.resize(newSize);
        std::cout << "Person removed!\n";
    }
}

void Commands::removeVehicle()
{
    int index = searchForVehicleIndex2();
    if(m_vehicles[index].hasOwner()) {
        m_vehicles[index].outputOwner();
        std::cout << "\nAre you sure you want to delete it? (y/n):";
        char answer;
        std::cin >> answer;
        bool key;
        answer == 'y' || answer == 'Y' ? key = true : key = false;
        if(key) {
            m_vehicles[index].removeOwner();
            m_vehicles.erase(m_vehicles.begin() + index);
            std::size_t newSyze = getVehiclesSize();
            m_vehicles.resize(newSyze);
            std::cout << "Vehicle removed!\n";
        }
    }

    else {
        m_vehicles.erase(m_vehicles.begin() + index);
        std::size_t newSyze = getVehiclesSize();
        m_vehicles.resize(newSyze);
        std::cout << "Vehicle removed!\n";
    }
}

void Commands::showPeople() const
{
    std::size_t size = getPeopleSize();

    if(size == 0) {
        std::cout << "There is no people stored in the data base.\n";
        return;
    }


    for(size_t index = 0; index < size; ++index) {
        std::cout << m_people[index] << '\n';
    }
}

void Commands::showVehicles() const
{
    std::size_t size = getVehiclesSize();

    if(size == 0) {
        std::cout << "There are no vehicles stored in the data base.\n";
        return;
    }

    for(size_t index = 0; index < size; ++index) {
        std::cout << m_vehicles[index] << '\n';
    }
}

void Commands::showPersonByID()
{
    int index = searchForPersonIndex();

    if(index != -1)
        m_people[index].outputVehicles();
    else
        std::cout << "There is no person with such ID.\n";
}

void Commands::showVehicleByReg()
{
    int index = searchForVehicleIndex2();

    if(index != -1)
        m_vehicles[index].outputOwner();
    else
        std::cout << "There is no vehicle with such registration.\n";
}
