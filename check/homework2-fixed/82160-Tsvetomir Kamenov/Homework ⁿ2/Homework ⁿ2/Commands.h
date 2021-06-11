#pragma once

#ifndef COMMANDS_H
#define COMMANDS_H

#include "Person.h"

class Commands
{
    enum {
        cmdVehicleLength = 7,
        cmdPersonLength = 6,
        cmdAcquireLength = 7,
        cmdReleaseLength = 7,
        cmdRemoveLength = 6,
        cmdSaveLength = 4,
        cmdShowLength = 4,
        cmdExitLength = 4,

        cmdLength7 = 7,
        cmdLength6 = 6,
        cmdLength4 = 4
    };

    std::vector<Person> m_people;
    std::vector<Vehicle> m_vehicles;
    std::vector<std::string> m_commands;

    void collectCommands();

    unsigned int convertStringToInt();
    bool isValidReg();
    bool isUniqueID();
    bool isUniqueReg();

    int searchForPersonIndex();
    int searchForVehicleIndex();
    int searchForVehicleIndex2();

    std::size_t getCommandLength() const;

    bool commandIsVehicle() const;
    bool commandIsPerson() const;
    bool commandIsAcquire() const;
    bool commandIsRelease() const;
    bool commandIsRemove() const;
    bool commandIsSave() const;
    bool commandIsShow() const;
    bool commandIsExit() const;

    std::string isIDorRegistration();

public:
    std::string command = "";
    std::string argument1 = "";
    std::string argument2 = "";
    bool exit = false;

    Commands() = default;

    std::size_t getPeopleSize() const;
    std::size_t getVehiclesSize() const;

    void addVehicle();
    void addPerson();
    void acquireVehicle();
    void releaseVehicle();
    void removePerson();
    void removeVehicle();
    void showPeople() const;
    void showVehicles() const;
    void showPersonByID();
    void showVehicleByReg();

    bool saveCommands();

    std::string interpretCommand();
    void CommandCentre();
};

#endif
