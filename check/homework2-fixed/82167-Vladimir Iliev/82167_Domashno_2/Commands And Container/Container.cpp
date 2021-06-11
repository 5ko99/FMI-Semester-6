#include "Container.h"
#include "Commands.h"

#include <cstring>
#include <fstream>

Container::~Container()
{
    size_t size = vehicleContainer.size();
    for (size_t i = 0; i < size; ++i)
        delete vehicleContainer[i];
    size = personContainer.size();
    for (size_t i = 0; i < size; ++i)
        delete personContainer[i];
}

size_t Container::findVehicle(const Vehicle& vehicle) const
{
    size_t size = vehicleContainer.size();
    for (size_t i = 0; i < size; ++i)
        if (strcmp(vehicle.getRegistration().c_str(), vehicleContainer.at(i)->getRegistration().c_str()) == 0)
            return i;
    throw std::invalid_argument("Vehicle not found");
}

size_t Container::findPerson(const Person& person) const
{
    size_t size = personContainer.size();
    for (size_t i = 0; i < size; i++)
        if (person.getID() == personContainer.at(i)->getID())
            return i;
    throw std::invalid_argument("Person not found");
}

void Container::removeVehicle(Vehicle* vehicle)
{
    size_t idx = findVehicle(*vehicle);
    delete vehicleContainer.at(idx);
    vehicleContainer.at(idx) = vehicleContainer.back();
    vehicleContainer.pop_back();
}

void Container::removePerson(Person* person)
{
    size_t idx = findPerson(*person);
    delete personContainer.at(idx);
    personContainer.at(idx) = personContainer.back();
    personContainer.pop_back();
}

size_t Container::findPerson(unsigned id) const
{
    size_t size = personContainer.size();
    for (size_t i = 0; i < size; ++i)
        if (id == personContainer.at(i)->getID())
            return i;
    throw std::invalid_argument("Person not found");
}

size_t Container::findVehicle(const char* registration) const
{
    size_t size = vehicleContainer.size();
    for (size_t i = 0; i < size; ++i)
        if (strcmp(registration, vehicleContainer.at(i)->getRegistration().c_str()) == 0)
            return i;
    throw std::invalid_argument("Vehicle not found");
}

Vehicle& Container::getVehicle(size_t idx)
{
    return *vehicleContainer.at(idx);
}

const Vehicle& Container::getVehicle(size_t idx) const
{
    return *vehicleContainer.at(idx);
}


Person& Container::getPerson(size_t idx)
{
    return *personContainer.at(idx);
}

const Person& Container::getPerson(size_t idx) const
{
    return *personContainer.at(idx);
}

void Container::removePerson(unsigned int id)
{
    size_t idx = findPerson(id);
    delete personContainer.at(idx);
    personContainer.at(idx) = personContainer.back();
    personContainer.pop_back();
}

void Container::removeVehicle(const char* registration)
{
    size_t idx = findVehicle(registration);
    delete vehicleContainer.at(idx);
    vehicleContainer.at(idx) = vehicleContainer.back();
    vehicleContainer.pop_back();
}

void Container::printVehicles() const
{
    size_t size = vehicleContainer.size();
    for (size_t i = 0; i < size; ++i)
        std::cout << *vehicleContainer[i] << "\n\n";
}

void Container::printPeople() const
{
    size_t size = personContainer.size();
    for (size_t i = 0; i < size; ++i)
        std::cout << *personContainer[i] << '\n';
}

void Container::saveToFile(const std::string& path)
{
    std::ofstream save_file(path.c_str());

    if (!save_file.is_open())
        throw std::invalid_argument("File not open");

    size_t size = vehicleContainer.size();
    for (size_t i = 0; i < size; ++i) {
        save_file << "VEHICLE " << vehicleContainer[i]->getRegistration() << " \""
                  << vehicleContainer[i]->getDescription() << "\" \n";
    }

    size = personContainer.size();
    for (size_t i = 0; i < size; ++i) {
        save_file << "PERSON \"" << personContainer[i]->getName()
                  << "\" " << personContainer[i]->getID() << '\n';
        size_t number_of_owned_vehicles = personContainer[i]->getOwnedVehicles().size();
        for (size_t j = 0; j < number_of_owned_vehicles; ++j)
            save_file << "ACQUIRE " << personContainer[i]->getID() << ' '
                      << personContainer[i]->getOwnedVehicles()[j]->getRegistration() << '\n';
    }

    save_file.close();
}

void Container::addVehicle(const std::string& registration, const std::string& description)
{
    try {
        findVehicle(registration.c_str());
    } catch (std::invalid_argument&) {
        vehicleContainer.emplace_back(new Vehicle(registration, description));
        return;
    }
    throw std::invalid_argument("The vehicle with this registration already exists");
}

void Container::addPerson(const std::string& name, unsigned id)
{
    try {
        findPerson(id);
    } catch (std::invalid_argument&) {
        personContainer.emplace_back(new Person(name, id));
        return;
    }
    throw std::invalid_argument("The person with this ID already exists");
}

void Container::loadFromFile(const char* path)
{
    std::ifstream load_file(path);
    if (!load_file.is_open())
        throw std::invalid_argument("loadfile not open");

    while (!load_file.eof()) {
        std::string cmd;
        std::getline(load_file, cmd, '\n');
        if (cmd.empty())
            continue;
        try {
            Command command(cmd.c_str());
            command.execute(*this);
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << '\n';
        }
    }
    load_file.close();
}
