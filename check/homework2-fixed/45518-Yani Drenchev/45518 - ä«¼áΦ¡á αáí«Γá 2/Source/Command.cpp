//
// Created by Yani Drenchev on 6.05.21.
//

#include "../Headers/Command.h"

#include <unordered_map>
#include <iostream>
/*РўСѓРє С‚Р°Р·Рё СЃС‚СЂСѓРєС‚СѓСЂР° РЅРё РїРѕР·РІРѕР»СЏРІР° Р»РµСЃРЅРѕ РІР±СЉРґРµС‰Рµ РґР° РґРѕР±Р°РІСЏРјРµ РЅРѕРІРё РєРѕРјР°РЅРґРё*/
struct CommandData {
    CommandCode code;
    unsigned noOfArguments;
};
//РљРѕРЅСЃС‚Р°РЅС‚РЅРё СЃР°, Р·Р°С‰РѕС‚Рѕ СЃР° С„РёРєСЃРёСЂР°РЅРё
const CommandData cmdNIL = {CommandCode::NIL, 0};

const std::unordered_map<std::string, CommandData> cmdList{
        {
                "VEHICLE", {CommandCode::VEHICLE, 2}},
        {
                "PERSON",  {CommandCode::PERSON,  2}},
        {
                "ACQUIRE", {CommandCode::ACQUIRE, 2}},
        {
                "RELEASE", {CommandCode::RELEASE, 2}},
        {
                "REMOVE",  {CommandCode::REMOVE,  1}},
        {
                "SAVE",    {CommandCode::SAVE,    1}},
        {
                "SHOW",    {CommandCode::SHOW,    1}},
        {
                "EXIT",    {CommandCode::EXIT,    0}}
};

const CommandData &getCommandInfo(const std::string &command) {
    auto it = cmdList.find(command);
    return it == cmdList.end() ? cmdNIL : it->second;
}
// РўРѕРІР° РїСЂРѕСЃС‚Рѕ СЂР°Р±РѕС‚Рё :)
std::string readArgument(std::string command, int index) {
    std::string argument;
    if (index >= command.size()) {
        return argument;
    }
    for (std::string::size_type i = index; i < command.size(); ++i) {
        if (command[i] == '"') {
            argument.push_back(command[i]);
            i++;
            while (command[i] != '"') {
                argument.push_back(command[i]);
                i++;
            }
            argument.push_back(command[i]);
            i++;
            break;
        }
        if (command[i] == ' ') {
            break;
        }
        argument.push_back(command[i]);
    }
    return argument;
}
// Р С‚РѕРІР° РїСЂРѕСЃС‚Рѕ СЂР°Р±РѕС‚Рё :)
Command parseCommand(const std::string &command) {
    int index = 0;
    std::string testCommand;
    for (std::string::size_type i = index; i < command.size(); ++i) {
        if (command[i] == ' ')
            break;
        testCommand.push_back(toupper(command[i]));
        ++index;
    }
    const auto cmdInfo = getCommandInfo(testCommand);
    if (cmdInfo.code == CommandCode::NIL)
        return {CommandCode::NIL, CommandArguments{}};

    ++index;

    CommandArguments arguments;

    for (std::string::size_type i = 0; i < 2; ++i) {
        std::string argument = readArgument(command, index);
        if (argument.empty())
            break;

        index += argument.size() +1;
        arguments.push_back(argument);
    }

    if (cmdInfo.noOfArguments != arguments.size())
        return {CommandCode::NIL, CommandArguments{}};

    return {cmdInfo.code, arguments};
}
