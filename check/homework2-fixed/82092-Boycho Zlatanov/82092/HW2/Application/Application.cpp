#ifndef Application_H
#define Application_H

#include <iostream>
#include <string>
#include <fstream>
#include "Application.hpp"

void Application::show(const std::string &input)
{
    if (input.compare("PEOPLE") == 0)
    {
        Database.showPeople();
    }
    else if (input.compare("Vehicles") == 0)
    {
        Database.showVehicles();
    }
    else if (input.compare("id") == 0)
    {
        Database.showID();
    }
}

void Application::save(const std::string &fileName)
{
    std::ofstream toSaveInto;
    toSaveInto.open(fileName, ios::out);
    if (!toSaveInto)
    {
        cout << "File not created!";
    }
    else
    {
        cout << "File opened successfully!";
        Datebase.serialize(fileName);
    }
}

void Application::start()
{
    std::cout << std::endl
              << "-------Welcome to the Department of Motor Vehicles Application-------"
              << std::endl;

    std::string userInput;

    do
    {
        std::cin.getline(userInput);
        std::string command = "";

        int i = 0;
        for (; i < userInput.length() && userInput[i] != ' '; ++i)
        {
            command += userInput[i];
        }
        ++i;

        if (command.compare("VEHICLE") == 0)
        {
            std::string numPlat = "";
            std::string description = "";

            for (; i < userInput.length() && userInput[i] != ' '; ++i)
            {
                numplate += userInput[i];
            }

            ++i;

            for (; i < userInput.length(); ++i)
            {
                description += userInput[i];
            }

            vehicle(numPlat, description);
        }

        else if (command.compare("PERSON") == 0)
        {
            std::string name = "";
            unsigned int ID = 0;

            for (; i < userInput.length() && userInput[i] != ' '; ++i)
            {
                name += userInput[i];
            }

            ++i;

            for (; i < userInput.length(); ++i)
            {
                ID *= 10;
                ID += userInput[i] - '0';
            }

            vehicle(name, ID);
        }
        else if (command.compare("ACQUIRE") == 0)
        {
            unsigned int personID = 0;
            std::string vehicleID = "";

            for (; i < userInput.length() && userInput[i] != ' '; ++i)
            {
                personID *= 10;
                personID += userInput[i] - '0';
            }

            ++i;

            for (; i < userInput.length(); ++i)
            {
                description += userInput[i];
            }

            Datebase.acquire(personID, vehicleID);
        }
        else if (command.compare("RELEASE") == 0)
        {
            unsigned int personID = 0;
            std::string vehicleID = "";

            for (; i < userInput.length() && userInput[i] != ' '; ++i)
            {
                personID *= 10;
                personID += userInput[i] - '0';
            }

            ++i;

            for (; i < userInput.length(); ++i)
            {
                description += userInput[i];
            }

            Datebase.release(personID, vehicleID);
        }
        else if (command.compare("REMOVE") == 0)
        {
            std::string toRemove = "";

            for (; i < userInput.length(); ++i)
            {
                toRemove += userInput[i];
            }

            Datebase.remove(toRemove);
        }
        else if (command.compare("SAVE") == 0)
        {
            std::string toSaveInto = "";

            for (; i < userInput.length(); ++i)
            {
                toSaveInto += userInput[i];
            }

            save(toSaveInto);
        }
        else if (command.compare("SHOW") == 0)
        {
            std::string toShow = "";

            for (; i < userInput.length(); ++i)
            {
                toShow += userInput[i];
            }

            show(toShow);
        }
        else
        {
            std::cout << std::endl
                      << "Invalid command! Make sure the file was properly initiated!"
                      << std::endl;
        }
    } while (true);
}

#endif
