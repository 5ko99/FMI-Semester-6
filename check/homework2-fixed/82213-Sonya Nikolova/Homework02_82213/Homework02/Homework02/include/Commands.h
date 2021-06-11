#pragma once
#include "Database.h"

#include <istream>
#include <ostream>
#include <string>

class VehicleCommand
{
private:
    std::string regNumber;
    std::string description;

public:
    VehicleCommand(const std::string & reg, const std::string & desc) : regNumber(reg), description(desc) {};
    VehicleCommand(const std::vector<std::string> &args);

    const std::string &getRegistrationNumber() const;
    const std::string &getDescription() const;
};

std::ostream & operator<<(std::ostream & stream, const VehicleCommand & cmd);

class PersonCommand
{
private:
    std::string name;
    unsigned int id;

public:
    PersonCommand(const std::string & name, const unsigned id) : name(name), id(id) {};
    PersonCommand(const std::vector<std::string> &args);

    const std::string &getName() const;
    unsigned int getId() const;
};

std::ostream & operator<<(std::ostream & stream, const PersonCommand & cmd);

class AcquireCommand
{
private:
    unsigned int personId;
    std::string vehicleRegNumber;

public:
    AcquireCommand(const unsigned id, const std::string & reg) : personId(id), vehicleRegNumber(reg) {};
    AcquireCommand(const std::vector<std::string> &args);

    const std::string &getVehicleRegNumber() const;
    unsigned int getPersonId() const;
};

std::ostream & operator<<(std::ostream & stream, const AcquireCommand & cmd);

class ReleaseCommand
{
private:
    unsigned int personId;
    std::string vehicleRegNumber;

public:
    ReleaseCommand(const std::vector<std::string> &args);

    const std::string &getVehicleRegNumber() const;
    unsigned int getPersonId() const;
};

class RemoveCommand
{
private:
    std::string what;

public:
    RemoveCommand(const std::vector<std::string> &args);
    const std::string &getThingToRemove() const;
};

class SaveCommand
{
private:
    std::string path;

public:
    SaveCommand(const std::vector<std::string> &args);
    const std::string &getPath() const;
};

class ShowCommand
{
private:
    std::string what;

public:
    ShowCommand(const std::vector<std::string> &args);
    const std::string &getThingToShow() const;
};
class CommandProcessor
{
private:
    DataBase &database;

    void processVehicleCmd(const VehicleCommand &cmd);
    void processPersonCmd(const PersonCommand &cmd);
    void processAcquireCmd(const AcquireCommand &cmd);
    void processReleaseCmd(const ReleaseCommand &cmd);
    void processRemoveCmd(const RemoveCommand &cmd);
    void processSaveCmd(const SaveCommand &cmd);
    void processShowCmd(const ShowCommand &cmd);

public:
    CommandProcessor(DataBase &database) : database(database){};
    void processCommand(const std::string &commandStr);
    void printMenu(std::ostream &stream);
    void printDataBase(std::ostream &stream);
    void loadDataBase(std::istream &stream, std::ostream * errorStream = nullptr);
};
