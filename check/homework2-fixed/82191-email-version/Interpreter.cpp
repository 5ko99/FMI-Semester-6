#include "Interpreter.h"

#include "Utils.h"
#include <cctype>
#include <algorithm>
#include <iostream>

Interpreter::Interpreter(const Database& database) : m_Database(database) {}

void Interpreter::ProcessShow(const std::vector<std::string>& args)
{
    if (args.size() == 2)
    {
        std::string arg1 = args[1];
        std::transform(arg1.begin(), arg1.end(), arg1.begin(), ::tolower);
        if (arg1 == "people")
        {
            m_Database.ShowPeople();
            return;
        }
        else if (arg1 == "vehicles")
        {
            m_Database.ShowVehicles();
            return;
        }
    } else if (args.size() >= 3)
    {
        std::string arg1 = args[1];
        std::transform(arg1.begin(), arg1.end(), arg1.begin(), ::tolower);
        try {
            if (arg1 == "people")
            {
                uint32_t id = std::stoi(args[2].c_str());
                m_Database.ShowPerson(id);
                return;
            }
            else if (arg1 == "vehicles")
            {
                std::string higher = args[2];
                std::transform(higher.begin(), higher.end(), higher.begin(), ::toupper);
                m_Database.ShowVehicle(higher);
                return;
            }
        } catch(const std::exception& ex) {
            throw;
        }
    }
    
    throw std::runtime_error("Invalid args");
}

void Interpreter::ProcessSave(const std::vector<std::string>& args)
{
    if (args.size() >= 2)
    {
        try {
            std::string res = "";
            uint32_t idx = 1;
            uint32_t idx2 = 1;
            if (args[idx2][0] == '"')
            {
                while (idx2 < args.size() && args[idx2][idx] != '"')
                {
                    res += args[idx2][idx];
                    idx++;
                    if (idx == args[idx2].size())
                    {
                        idx2++;
                        idx = 0;
                        res += ' ';
                    }
                }
            }
            else res = args[1];
            m_Database.Save(res);
            return;
        }
        catch (const std::exception& ex) {
            throw;
        }
    }
    else
        throw std::runtime_error("Invalid args");
}

void Interpreter::ProcessRemove(const std::vector<std::string>& args)
{
    if (args.size() == 2)
    {
        const std::string& what = args[1];
        if ('0' <= what[0] && what[0] <= '9') // person
        {
            try {
                uint32_t id = std::stoi(what.c_str());
                m_Database.RemovePerson(id);
                return;
            } catch(const std::exception& ex) {
                throw;
            }
        } else { // car reg
            try {
                std::string higher = what;
                std::transform(higher.begin(), higher.end(), higher.begin(), ::toupper);
                m_Database.RemoveVehicle(higher);
                return;
            } catch(const std::exception& ex) {
                throw;
            }
        }
    }
    else
        throw std::runtime_error("Invalid args");
}

void Interpreter::ProcessRelease(const std::vector<std::string>& args)
{
    if (args.size() >= 3)
    {
        try {
            uint32_t personId = std::stoi(args[1]);
            std::string higher = args[2];
            std::transform(higher.begin(), higher.end(), higher.begin(), ::toupper);
            m_Database.Release(personId, higher);
            return;
        } catch(const std::exception& ex) {
            throw;
        }
    }
    else
        throw std::runtime_error("Invalid args");
}

void Interpreter::ProcessAcquire(const std::vector<std::string>& args)
{
    if (args.size() >= 3)
    {
        try {
            uint32_t personId = std::stoi(args[1]);
            std::string higher = args[2];
            std::transform(higher.begin(), higher.end(), higher.begin(), ::toupper);
            m_Database.Acquire(personId, higher);
            return;
        } catch(const std::exception& ex) {
            throw;
        }
    }
    else
        throw std::runtime_error("Invalid args");
}

void Interpreter::ProcessInsertPerson(const std::vector<std::string>& args)
{
    if (args.size() >= 3)
    {
        try {
            std::string res = "";
            std::string idstr = args[2];
            uint32_t idx = 1;
            uint32_t idx2 = 1;
            if (args[idx2][0] == '"')
            {
                while (idx2 < args.size() && args[idx2][idx] != '"')
                {
                    res += args[idx2][idx];
                    idx++;
                    if (idx == args[idx2].size())
                    {
                        idx2++;
                        idx = 0;
                        res += ' ';
                    }
                }
            }
            else res = args[1];
            if (args.size() > 3)
            {
                idstr = args[idx2 + 1];
            }
            uint32_t personId = std::stoi(idstr);
            m_Database.InsertPerson(res, personId);
            return;
        } catch(const std::exception& ex) {
            throw;
        }
    }
    else
        throw std::runtime_error("Invalid args");
}

void Interpreter::ProcessInsertVehicle(const std::vector<std::string>& args)
{
    if (args.size() >= 3)
    {
        try {
            std::string res = "";
            uint32_t idx = 1;
            uint32_t idx2 = 2;
            if (args[idx2][0] == '"')
            {
                while (idx2 < args.size() && args[idx2][idx] != '"')
                {
                    res += args[idx2][idx];
                    idx++;
                    if (idx == args[idx2].size())
                    {
                        idx2++;
                        idx = 0;
                        res += ' ';
                    }
                }
            }
            else res = args[2];
            std::string higher = args[1];
            std::transform(higher.begin(), higher.end(), higher.begin(), ::toupper);
            m_Database.InsertVehicle(higher, res);
            return;
        } catch(const std::exception& ex) {
            throw;
        }
    }
    else
        throw std::runtime_error("Invalid args");
}

void Interpreter::ShowHelp()
{
    std::cout << "VEHICLE <registration> <description>" << '\n' <<
        "PERSON <name> <id>" << '\n' <<
        "ACQUIRE <owner-id> <vehicle-id>" << '\n' <<
        "RELEASE <owner-id> <vehicle-id>" << '\n' <<
        "REMOVE <what>" << '\n' << "SAVE <path>" << '\n' <<
        "SHOW [PEOPLE|VEHICLES|<id>" << std::endl;
}

void Interpreter::Process(const std::string& line)
{
    auto args = Utils::SplitString(line, " ");
    std::string& command = args[0];
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    if (command == "show")
        ProcessShow(args);
    else if (command == "save")
        ProcessSave(args);
    else if (command == "remove")
        ProcessRemove(args);
    else if (command == "release")
        ProcessRelease(args);
    else if (command == "acquire")
        ProcessAcquire(args);
    else if (command == "person")
        ProcessInsertPerson(args);
    else if (command == "vehicle")
        ProcessInsertVehicle(args);
    else if (command == "help")
        ShowHelp();
    else throw std::runtime_error("Invalid command");
}
