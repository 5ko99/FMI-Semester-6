#pragma once

#include <string>
#include <cstring>

#include "Vehicle.h"
#include "Person.h"
#include "Container.h"

enum class COMMANDS {
    UNKNOWN = -1,
    VEHICLE,
    PERSON,
    ACQUIRE,
    RELEASE,
    REMOVE,
    SAVE,
    SHOW,
    EXIT
};

class Command {
    std::string cmd;
    std::vector<std::string> arguments;
    COMMANDS cmdType;

    //Ensuring the command is valid.
    static COMMANDS isValidCommand(const char* cmd);
    static char toLowerCase(char a);
    static bool isEmptyCharacter(char a);
    static bool isNumber(char i);
    static bool isUnsignedInt(const std::string& str);
    static unsigned strToUnsigned(const std::string& str);

    //Executing the commands.
    void createNewVehicle(Container& container);
    void createNewPerson(Container& container);
    void acquireVehicle(Container& container);
    void releaseVehicle(Container& container);
    void remove(Container& container);
    void save(Container& container);
    void show(Container& container);

public:
    explicit Command(const char* cmd);
    bool execute(Container& container); // Returns true if command is exit, false otherwise.
};




































//class Container {
//protected:
//    std::vector<Person*> personContainer;
//    std::vector<Vehicle*> vehicleContainer;
//
//    Container() = default;
//    Vehicle* vehicleFind(const char* reg);
//    Person* personFind(unsigned id);
//
//public:
//
//    virtual ~Container();
//    const Vehicle* getVehicle(size_t idx) const;
//};
//
//class Command : public Container {
//protected:
//    std::string cmd;
//    std::string arguments;
//    COMMANDS type = COMMANDS::UNKNOWN;
//
//    static char toLowerCase(char a);
//    explicit Command(const char* cmd);
//
//public:
//    Command(const Command&) = delete;
//    Command& operator=(const Command&) = delete;
//    ~Command() override = default;
//
//    static COMMANDS cmd_type(const char* cmd);
////    const std::string& getCommand() const;
////    const std::string& getArguments() const;
////    const COMMANDS& getType() const;
//    virtual void execute() = 0;
//
//};
//
//class vehicle_cmd : public Command {
//    std::string arg1;
//    std::string arg2;
//
//public:
//    explicit vehicle_cmd(const char* cmd);
//    ~vehicle_cmd() override = default;
//
//    void execute() override;
//};
//
//class person_cmd : public Command {
//    std::string arg1;
//    unsigned arg2;
//
//    static bool isUint(const char* str);
//
//public:
//    explicit person_cmd(const char* cmd);
//    ~person_cmd() override = default;
//
//    void execute() override;
//};

//#include <stdexcept>
//#include "Commands.h"
//
//char Command::toLowerCase(char a)
//{
//    if ('A' <= a && a <= 'Z')
//        return (a - 'A' + 'a');
//    return a;
//}
//
//Command::Command(const char* cmd)
//        : Container()
//{
//    if (!cmd)
//        throw std::invalid_argument("Invalid command");
//    size_t len = strlen(cmd);
//    size_t i = 0;
//    while (cmd[i] != ' ' && i < len) {
//        this->cmd.push_back(toLowerCase(cmd[i]));
//        ++i;
//    }
//    if (i == len)
//        throw std::invalid_argument("No arguments passed");
//    type = cmd_type(cmd);
//    if (type == COMMANDS::UNKNOWN)
//        throw std::invalid_argument("Invalid command");
//    while (cmd[i] == ' ')
//        i++;
//    while (i < len) {
//        arguments.push_back(cmd[i]);
//        ++i;
//    }
//}
//
//COMMANDS Command::cmd_type(const char* cmd)
//{
//    char _cmd[8];
//    for (short i = 0; i < 8 && cmd[i] != ' '; ++i)
//        _cmd[i] = toLowerCase(cmd[i]);
//    _cmd[7] = '\0';
//
//    const short available_cmds = 7;
//    const char* commands[available_cmds] = {"vehicle",
//                                            "person",
//                                            "acquire",
//                                            "release",
//                                            "remove",
//                                            "save",
//                                            "show"};
//    for (short i = 0; i < available_cmds; ++i)
//        if (strcmp(_cmd, commands[i]) == 0)
//            return (COMMANDS) i;
//
//    return COMMANDS::UNKNOWN;
//}
//
////const std::string& Command::getCommand() const
////{ return cmd; }
////
////const std::string& Command::getArguments() const
////{ return arguments; }
////
////const COMMANDS& Command::getType() const
////{ return type; }
//
//
//vehicle_cmd::vehicle_cmd(const char* cmd)
//        : Command(cmd)
//{
//    size_t pos = 0;
//    size_t len = arguments.length();
//    while (arguments.at(pos) != ' ' && pos < len) //Separate first argument
//        arg1.push_back(arguments.at(pos++));
//    if (pos == len)
//        throw std::invalid_argument("VEHICLE: not enough arguments");
//    while (arguments.at(pos) == ' ' && pos < len) //Skip blank spaces
//        pos++;
//    if (pos == len)
//        throw std::invalid_argument("VEHICLE: not enough arguments");
//    while (pos < len) //Separate first argument
//        arg2.push_back(arguments.at(pos++));
//}
//
//void vehicle_cmd::execute()
//{
//    vehicleContainer.push_back(new Vehicle(arg1, arg2));
//}
//
//
//person_cmd::person_cmd(const char* cmd)
//        : Command(cmd)
//{
//    size_t pos = 0;
//    size_t len = arguments.length();
//    std::string arg2;
//    while (arguments.at(pos) != ' ' && pos < len) //Separate first argument
//        arg1.push_back(arguments.at(pos++));
//    if (pos == len)
//        throw std::invalid_argument("VEHICLE: not enough arguments");
//    while (arguments.at(pos) == ' ' && pos < len) //Skip blank spaces
//        pos++;
//    if (pos == len)
//        throw std::invalid_argument("VEHICLE: not enough arguments");
//    while (pos < len) //Separate first argument
//        arg2.push_back(arguments.at(pos++));
//
//    if (type == COMMANDS::PERSON) {
//        if (!isUint(arg2.c_str()))
//            throw std::invalid_argument("VEHICLE: not enough arguments");;
//        this->arg2 = (unsigned) atoi(arg2.c_str());
//    } else {
//        if (!isUint(arg1.c_str()))
//            throw std::invalid_argument("VEHICLE: not enough arguments");;
//        this->arg2 = (unsigned) atoi(arg1.c_str());
//        arg1 = std::move(arg2);
//    }
//}
//
//void person_cmd::execute()
//{
//    switch (type) {
//        case COMMANDS::PERSON:
//            personContainer.push_back(new Person(arg1, arg2));
//            break;
//        case COMMANDS::ACQUIRE:
//            personFind(arg2)->addVehicle(*vehicleFind(arg1.c_str()));
//            break;
//        case COMMANDS::RELEASE:
//            personFind(arg2)->removeVehicle(*vehicleFind(arg1.c_str()));
//            break;
//    }
//}
//
//bool person_cmd::isUint(const char* str)
//{
//    size_t len = strlen(str);
//    if (!str || str[0] == '-') return false;
//    for (size_t i = 0; i < len; ++i)
//        if ('0' > str[i] || str[i] > '9')
//            return false;
//    return true;
//}
//
//Vehicle* Container::vehicleFind(const char* reg)
//{
//    if (!reg)
//        throw std::invalid_argument("Invalid registration");
//    size_t vContSize = vehicleContainer.size();
//    for (size_t i = 0; i < 0; ++i)
//        if (strcmp(reg, vehicleContainer[i]->getRegistration().c_str()) == 0)
//            return vehicleContainer[i];
//    throw std::invalid_argument("Vehicle not found");
//}
//
//Person* Container::personFind(unsigned int id)
//{
//    size_t vec_size = personContainer.size();
//    for (size_t i = 0; i < vec_size; ++i)
//        if (id == personContainer[i]->getID())
//            return personContainer[i];
//    throw std::invalid_argument("Person not found");
//}
//
//Container::~Container()
//{
//    size_t size = vehicleContainer.size();
//    for (size_t i = 0; i < size; ++i)
//        delete vehicleContainer[i];
//    size = personContainer.size();
//    for (size_t i = 0; i < size; ++i)
//        delete personContainer[i];
//}
//
//const Vehicle* Container::getVehicle(size_t idx) const
//{ return vehicleContainer.at(idx); }


