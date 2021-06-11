#pragma once

#include "../include/Command.hpp"

#include <fstream>

class UnaryCommand : public Command
{
public:
    UnaryCommand(const std::string &name, Executor &exec)
        : Command(name, exec) {}

    void execute(std::istringstream &arguments);

protected:
    bool checkId(const std::string &id) const;

    virtual void process(std::string arg) = 0;
};

class RemoveCommand : public UnaryCommand
{
public:
    RemoveCommand(Executor &exec)
        : UnaryCommand("REMOVE", exec)
    {
    }

protected:
    void process(std::string arg)
    {
        if (checkId(arg))
        {
            int id = stoi(arg);
            for (Person *person : getExecutor().people)
            {
                if (person->getId() == id)
                {
                    for (Vehicle *vehicle : getExecutor().vehicles)
                    {
                        if (vehicle->getOwner()->getId() == id)
                        {
                            vehicle->setOwner(nullptr);
                        }
                    }
                    getExecutor().people.remove(person);
                    return;
                }
            }
        }
        else
        {
            for (Vehicle *vehicle : getExecutor().vehicles)
            {
                if (vehicle->getNum() == arg)
                {
                    vehicle->setOwner(nullptr);
                    getExecutor().vehicles.remove(vehicle);
                    return;
                }
            }
        }
        std::cout << "No such objec was found.";
    }
};

class ShowCommand : public UnaryCommand
{
public:
    ShowCommand(Executor &exec)
        : UnaryCommand("SHOW", exec)
    {
    }

protected:
    void process(std::string arg)
    {
        if (getExecutor().str_tolower(arg) == getExecutor().str_tolower("PEOPLE"))
        {
            for (Person *person : getExecutor().people)
            {
                std::cout << person->getId() << " " << person->getName() << std::endl;
                return;
            }
        }
        if (getExecutor().str_tolower(arg) == getExecutor().str_tolower("VEHICLES"))
        {
            for (Vehicle *vehicle : getExecutor().vehicles)
            {
                std::cout << vehicle->getNum() << " " << vehicle->getDescription();
                if (vehicle->getOwner() != nullptr)
                {
                    std::cout << vehicle->getOwner()->getName() << " " << vehicle->getOwner()->getId();
                }
                std::cout << std::endl;
                return;
            }
        }
        else
        {
            if (checkId(arg))
            {
                int id = stoi(arg);
                for (Person *person : getExecutor().people)
                {
                    if (person->getId() == id)
                    {
                        std::cout << person->getName() << " " << person->getId();
                        for (Vehicle *vehicle : person->getCarsRead())
                        {
                            std::cout << " " << vehicle->getNum();
                        }
                        std::cout << std::endl;
                        break;
                    }
                }
            }
            else
            {
                for (Vehicle *vehicle : getExecutor().vehicles)
                {
                    if (vehicle->getNum() == arg)
                    {
                        std::cout << vehicle->getOwner()->getId() << " "
                                  << vehicle->getOwner()->getName() << std::endl;
                        break;
                    }
                }
            }
        }
    }
};

class SaveCommand : public UnaryCommand
{
public:
    SaveCommand(Executor &exec)
        : UnaryCommand("SAVE", exec)
    {
    }

protected:
    void process(std::string arg)
    {
        std::ofstream MyFile(arg);
        for (Person* person : getExecutor().people)
        {
            MyFile << "PERSON " << person->getName() << " " << person->getId();
        }
        for (Vehicle* vehicle : getExecutor().vehicles)
        {
            MyFile << "VEHICLE " << vehicle->getNum() << " " << vehicle->getDescription();
            if (vehicle->getOwner() != nullptr){
                MyFile << "ACQUIRE " << vehicle->getOwner()->getId() << " " << vehicle->getNum();
            }
        }

        MyFile.close();
    }
};
