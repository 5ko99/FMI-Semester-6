#include "Commands.h"

#include <stdexcept>
#include <fstream>

#include "commandTokenizer.h"

// VehicleCommand
VehicleCommand::VehicleCommand(const std::vector<std::string> &args)
{
    if (args.size() != 2)
        throw std::invalid_argument("Vehicle command requires exactly 2 arguments");
    this->regNumber = args[0];
    this->description = args[1];
}

const std::string &VehicleCommand::getRegistrationNumber() const
{
    return this->regNumber;
}

const std::string &VehicleCommand::getDescription() const
{
    return this->description;
}

std::ostream & operator<<(std::ostream & stream, const VehicleCommand & cmd)
{
    stream << "acquire " << cmd.getRegistrationNumber() << " " << cmd.getDescription();
    return stream;
}

// PersonCommand
PersonCommand::PersonCommand(const std::vector<std::string> &args)
{
    if (args.size() != 2)
        throw std::invalid_argument("Person command requires exactly 2 arguments");
    this->name = args[0];
    this->id = std::stoi(args[1]);
}

const std::string &PersonCommand::getName() const
{
    return this->name;
}
unsigned int PersonCommand::getId() const
{
    return this->id;
}

std::ostream & operator<<(std::ostream & stream, const PersonCommand & cmd)
{
    stream << "person \"" << cmd.getName() << "\" " << cmd.getId();
    return stream;
}

// AcquireCommand
AcquireCommand::AcquireCommand(const std::vector<std::string> &args)
{
    if (args.size() != 2)
        throw std::invalid_argument("Acquire command requires exactly 2 arguments");
    this->personId = std::stoi(args[0]);
    this->vehicleRegNumber = args[1];
}

const std::string &AcquireCommand::getVehicleRegNumber() const
{
    return this->vehicleRegNumber;
}

unsigned int AcquireCommand::getPersonId() const
{
    return this->personId;
}

std::ostream & operator<<(std::ostream & stream, const AcquireCommand & cmd)
{
    stream << "acquire " << cmd.getPersonId() << " " << cmd.getVehicleRegNumber();
    return stream;
}

// ReleaseCommand
ReleaseCommand::ReleaseCommand(const std::vector<std::string> &args)
{
    if (args.size() != 2)
        throw std::invalid_argument("Release command requires exactly 2 arguments");
    this->personId = std::stoi(args[0]);
    this->vehicleRegNumber = args[1];
}
const std::string &ReleaseCommand::getVehicleRegNumber() const
{
    return this->vehicleRegNumber;
}

unsigned int ReleaseCommand::getPersonId() const
{
    return this->personId;
}

// RemoveCommand
RemoveCommand::RemoveCommand(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        throw std::invalid_argument("Remove command requires exactly 1 argument");
    }
    this->what = args[0];
}

const std::string &RemoveCommand::getThingToRemove() const
{
    return this->what;
}

// SaveCommand
SaveCommand::SaveCommand(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        throw std::invalid_argument("Save command requires exactly 1 argument");
    }
    this->path = args[0];
}

const std::string &SaveCommand::getPath() const
{
    return this->path;
}

// ShowCommand
ShowCommand::ShowCommand(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        throw std::invalid_argument("Show command requires exactly 1 argument");
    }
    this->what = args[0];
}

const std::string &ShowCommand::getThingToShow() const
{
    return this->what;
}

// CommandProcessor
void CommandProcessor::printMenu(std::ostream &stream)
{
    stream << "VEHICLE <registration> <description>" << std::endl;
    stream << "PERSON <name> <id>" << std::endl;
    stream << "ACQUIRE <owner-id> <vehicle-id>" << std::endl;
    stream << "RELEASE <owner-id> <vehicle-id>" << std::endl;
    stream << "REMOVE <what>" << std::endl;
    stream << "SAVE <path> " << std::endl;
    stream << "SHOW [ PEOPLE| VEHICLES | <id> ]" << std::endl;
}

void CommandProcessor::processCommand(const std::string &commandStr)
{
    const CommandTokens tokens = tokenize(commandStr);

    // Tokenizer always returns lower-case commands
    if (tokens.command == "vehicle")
    {
        VehicleCommand cmd(tokens.arguments);
        this->processVehicleCmd(cmd);
    }
    else if (tokens.command == "person")
    {
        PersonCommand cmd(tokens.arguments);
        this->processPersonCmd(cmd);
    }
    else if (tokens.command == "acquire")
    {
        AcquireCommand cmd(tokens.arguments);
        this->processAcquireCmd(cmd);
    }
    else if (tokens.command == "release")
    {
        ReleaseCommand cmd(tokens.arguments);
        this->processReleaseCmd(cmd);
    }
    else if (tokens.command == "remove")
    {
        RemoveCommand cmd(tokens.arguments);
        this->processRemoveCmd(cmd);
    }
    else if (tokens.command == "save")
    {
        SaveCommand cmd(tokens.arguments);
        this->processSaveCmd(cmd);
    }
    else if (tokens.command == "show")
    {
        ShowCommand cmd(tokens.arguments);
        this->processShowCmd(cmd);
    }
    else
    {
        throw std::invalid_argument("Unknown command: " + tokens.command);
    }
}

void CommandProcessor::processVehicleCmd(const VehicleCommand &cmd)
{
    Registration vehicleRegistration(cmd.getRegistrationNumber());
    this->database.addVehicle(vehicleRegistration, cmd.getDescription());
}

void CommandProcessor::processPersonCmd(const PersonCommand &cmd)
{
    this->database.addPerson(cmd.getName(), cmd.getId());
}

void CommandProcessor::processAcquireCmd(const AcquireCommand &cmd)
{
    this->database.assignVehicleToPerson(cmd.getPersonId(), cmd.getVehicleRegNumber());
}

void CommandProcessor::processReleaseCmd(const ReleaseCommand &cmd)
{
    this->database.releaseVehicleFromPerson(cmd.getPersonId(), cmd.getVehicleRegNumber());
}

void CommandProcessor::processRemoveCmd(const RemoveCommand &cmd)
{
   const std::string what = cmd.getThingToRemove();

   if((what.size() == 7 && what[6] >= 'A' && what[6]  <= 'Z' ) || (what.size() == 8  && what[7] >= 'A' && what[7] <= 'Z'))
   {
       Registration reg(what);
       this->database.removeVehicle(reg);
   }
   else
   {
       unsigned int id = std::stoi(what);
       this->database.removePerson(id);
   }
}

void CommandProcessor::processSaveCmd(const SaveCommand &cmd)
{
    const std::string path = cmd.getPath();

    bool fileExists = false;
    {
        std::ifstream testFile(path);
        if (testFile.is_open())
        {
            fileExists = true;
        }
    }

    bool proceed = true;

    if (fileExists)
    {
        std::cout << "File " << path << " exists, overwrite? [y/n] ";
        std::string line;
        std::getline(std::cin, line);
        if (line.size() < 1 || line[0] != 'y') proceed = false;
    }

    if (!proceed) return;

    std::ofstream outFile(path);
    this->printDataBase(outFile);
}

void CommandProcessor::processShowCmd(const ShowCommand &cmd)
{
    const std::string what = cmd.getThingToShow();
    if (what == "people")
    {
        const auto people = this->database.getAllPeopleIds();
        // Print all people
        for (int i = 0; i < people.size(); i++)
        {
            const Person * p = this->database.getPerson(people[i]);
            if (!p) throw std::runtime_error("Person was deleted when they shouldn't have been");
            std::cout << p->getId() << "\n";
        }
    }
    else if (what == "vehicles")
    {
        const auto vehicles = this->database.getAllVehicleRegistrations();
        // Print all vehicles
        for (int i = 0; i < vehicles.size(); i++)
        {
            const Vehicle * v = this->database.getVehicle(vehicles[i]);
            if (!v) throw std::runtime_error("Vehicle was deleted when it shouldn't have been");
            std::cout << v->getRegistration().getNumber() << "\n";
        }
    }
    else
    {
        const Vehicle * v = 0;
        const Person * p = 0;

        try
        {
            Registration reg(what);
            v = this->database.getVehicle(reg);
        }
        catch(const std::exception& e)
        {
        }
        
        try
        {
            unsigned id = std::stoi(what);
            p = this->database.getPerson(id);
        }
        catch(const std::exception& e)
        {
        }
        
        if (v)
        {
            const Person * owner = v->getOwner();
            std::cout << "Vehicle " << v->getRegistration().getNumber() << " " << v->getDescription();
            if (owner)
            {
                std::cout << " - owned by " << owner->getId() << "\n";
            }
            else std::cout << " - no owner\n";
        }
        else if (p)
        {
            std::cout << "Person " << p->getName() << " " << p->getId() << "\n";
            const auto ownedVehicles = p->cntOfVehicles();
            if (ownedVehicles)
            {
                std::cout << "Owned vehicles:\n";
                p->printOwnedVehicles(std::cout);
            }
            else
            {
                std::cout << "Doesn't own any vehicles\n";
            }
        }
        else
        {
            throw std::invalid_argument(what + " is not either a vehicle or person ID");
        }
    }
}

void CommandProcessor::printDataBase(std::ostream &stream)
{
    // Retrieve all vehicles + people
    const auto vehicles = this->database.getAllVehicleRegistrations();
    const auto people = this->database.getAllPeopleIds();

    // Print all people
    for (int i = 0; i < people.size(); i++)
    {
        const Person * p = this->database.getPerson(people[i]);
        if (!p) throw std::runtime_error("Person was deleted when they shouldn't have been");
        PersonCommand cmd(p->getName(), p->getId());
        stream << cmd << "\n";
    }

    // Print all vehicles
    for (int i = 0; i < vehicles.size(); i++)
    {
        const Vehicle * v = this->database.getVehicle(vehicles[i]);
        if (!v) throw std::runtime_error("Vehicle was deleted when it shouldn't have been");
        VehicleCommand cmd(v->getRegistration().getNumber(), v->getDescription());
        stream << cmd << "\n";

        // People are already printed, so if a vehicle has an owner
        // we can safely output an acquire command
        const Person * owner = v->getOwner();
        if (owner)
        {
            AcquireCommand aCmd(owner->getId(), owner->getName());
            stream << cmd << "\n";
        }
    }
}

void CommandProcessor::loadDataBase(std::istream &stream, std::ostream * errorStream)
{
    std::string line;
    int lineId = -1;
    while (std::getline(stream, line))
    {
        lineId++;

        // Perform checks on a per-line basis
        try
        {
            this->processCommand(line);
        }
        catch(const std::exception& e)
        {
            if (errorStream)
            {
                *errorStream << "Line " << lineId << " error: " << e.what() << '\n';
            }
        }
    }
}
