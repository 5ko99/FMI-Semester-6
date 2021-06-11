#pragma once

#include <string>
#include <vector>

#include "Vehicle.h"

class CommandParser {
private:
    std::vector<Person *> people;

    std::vector<Vehicle *> vehicles;


public:
    CommandParser() = default;

    CommandParser(const CommandParser &object) = delete;

    ~CommandParser();

public:

    std::vector<Person *> getPeople() const;

    std::vector<Vehicle *> getVehicles() const;

public:
    void parseCommand(std::string &command);

private:
    void createVehicle(const std::string &registration, const std::string &description);

    void createPerson(const std::string &name, int id);

    void acquireVehicle(int personId, const std::string &registration);

    void releaseVehicle(int personId, const std::string &registration);

    void removePerson(int personId);

    void removeVehicle(const std::string &registration);

    void saveData(std::string &path);

    void saveHelper(const std::string &path);

    void printPerson(int personId);

    void printVehicle(const std::string &registration);

    void printAll(const std::string &command);

private:
    std::vector<std::string> split(std::string &command);

    int findVehicle(const std::string &registration) const;

    int findPerson(const unsigned int id);

    void toLower(std::string &command);

    void validateCommand(const std::vector<std::string> &commands) const;

    void validateRegistration(const std::string &string);

    bool isCapLetter(const char &symbol) const;

    bool isNumber(const char &symbol) const;

private:
    CommandParser &operator=(const CommandParser &object);
};

