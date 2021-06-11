#include "../include/Command.hpp"
#include "../include/Executor.hpp"

class BinaryCommand : public Command
{
public:
    BinaryCommand(const std::string &name, Executor &exec) : Command(name, exec) {}

    void execute(std::istringstream &arguments);

protected:
    virtual void process(std::string arg1, std::string arg2) = 0;
};

class VehicleCommand : public BinaryCommand
{
public:
    VehicleCommand(Executor &exec)
        : BinaryCommand("VEHICLE", exec)
    {
    }

protected:
    void process(std::string arg1, std::string arg2)
    {
        getExecutor().vehicles.push_back(new Vehicle((arg1), arg2));
    }
};

class PersonCommand : public BinaryCommand
{
public:
    PersonCommand(Executor &exec)
        : BinaryCommand("PERSON", exec)
    {
    }

protected:
    void process(std::string arg1, std::string arg2)
    {
        getExecutor().people.push_back(new Person(arg1, stoi(arg2)));
    }
};

class AcquireCommand : public BinaryCommand
{
public:
    AcquireCommand(Executor &exec)
        : BinaryCommand("ACQUIRE", exec)
    {
    }

protected:
    void process(std::string arg1, std::string arg2)
    {
        for (Person *person : getExecutor().people)
        {
            if (person->getId() == stoi(arg1))
            {
                for (Vehicle *vehicle : getExecutor().vehicles)
                {
                    if (vehicle->getNum() == arg2)
                    {
                        person->addCar(vehicle);
                        return;
                    }
                }
            }
        }
    }
};

class ReleaseCommand : public BinaryCommand
{
public:
    ReleaseCommand(Executor &exec)
        : BinaryCommand("RELEASE", exec)
    {
    }

protected:
    void process(std::string arg1, std::string arg2)
    {
        for (Person *person : getExecutor().people)
        {
            if (person->getId() == stoi(arg1))
            {
                for (Vehicle *vehicle : person->getCarsRead())
                {
                    if (vehicle->getOwner()->getId() == person->getId())
                    {
                        vehicle->setOwner(nullptr);
                        return;
                    }
                }
            }
        }
    }
};
