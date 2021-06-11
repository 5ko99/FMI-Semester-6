#include "Database.h"

#include <algorithm>

DataBase::DataBase() {}

DataBase::~DataBase()
{
    const size_t lenPeople = this->people.size();
    const size_t lenVehicles = this->vehicles.size();

    for (size_t i = 0; i < lenPeople; i++)
    {
        delete this->people[i];
        this->people[i] = nullptr;
    }

    for (size_t k = 0; k < lenVehicles; k++)
    {
        delete this->vehicles[k];
        this->vehicles[k] = nullptr;
    }
}

Person *DataBase::findPerson(const unsigned int id)
{
    const size_t len = this->people.size();

    for (size_t i = 0; i < len; i++)
    {
        Person *p = this->people[i];
        if (p->getId() == id)
        {
            return p;
        }
    }
    return nullptr;
}

Vehicle *DataBase::findVehicle(const Registration &reg)
{
    const size_t len = this->vehicles.size();

    for (size_t i = 0; i < len; i++)
    {
        Vehicle *v = vehicles[i];
        if (v->getRegistration() == reg)
        {
            return v;
        }
    }
    return nullptr;
}

//helper functions
bool DataBase::doesPersonExist(const unsigned int id)
{
    return this->findPerson(id) != nullptr;
}

bool DataBase::doesVehicleExist(const Registration &registration)
{
    return this->findVehicle(registration) != nullptr;
}

void DataBase::addPerson(const std::string &name, const unsigned int id)
{
    if (!doesPersonExist(id))
    {

        this->people.push_back(new Person(name, id));
        std::cout << "Person with id " << id << " was successfully created." << std::endl;
    }
    else
    {
        throw std::invalid_argument("Person with ID " + std::to_string(id) + " already exists\n");
    }
}

void DataBase::addVehicle(const Registration &registration, const std::string &description)
{
    if (!doesVehicleExist(registration))
    {
        this->vehicles.push_back(new Vehicle(registration, description));
        std::cout << "Vehicle with registration " << registration.getNumber() << " was successfully created." << std::endl;
    }
    else
    {
        throw std::invalid_argument("Vehicle with reg #" + std::string(registration.getNumber()) + " already exists\n");
    }
}

void DataBase::assignVehicleToPerson(const unsigned int owner_id, const Registration &registration)
{
    Person *person = this->findPerson(owner_id);
    Vehicle *vehicle = this->findVehicle(registration);

    if (!person || !vehicle)
    {
        throw std::invalid_argument("Person or vehicle doesn't exist");
    }

    // Remove vehicle from old owner, if they exist
    Person *oldOwner = vehicle->getOwner();
    if (oldOwner)
    {
        oldOwner->removeVehicle(vehicle);
    }

    person->addVehicle(vehicle);
    vehicle->setOwner(*person);

    std::cout << "Vehicle with registration " << registration.getNumber() << " was successfully assigned to person with id " << person->getId() << std::endl;
}

void DataBase::releaseVehicleFromPerson(const unsigned int owner_id, const Registration &registration)
{
    Person *person = this->findPerson(owner_id);
    Vehicle *vehicle = this->findVehicle(registration);

    if (!person || !vehicle)
    {
        throw std::invalid_argument("Person or vehicle doesn't exist");
    }

    person->removeVehicle(vehicle);
    vehicle->clearOwner();
    std::cout << "Vehicle with registration " << registration.getNumber() << " was successfully released from person with id " << person->getId() << std::endl;
}

void DataBase::printPerson(const unsigned int id)
{
    Person *person = findPerson(id);

    if (person == nullptr)
    {
        std::cout << "Person with id " << id << " doesn't exist in the database" << std::endl;
        return;
    }

    std::cout << person->getName() << " " << person->getId();
    person->printOwnedVehicles(std::cout);
    std::cout << std::endl;
}

void DataBase::printVehicle(const Registration &registration)
{
    Vehicle *vehicle = findVehicle(registration);

    if (vehicle == nullptr)
    {
        std::cout << "Vehicle with registration " << registration.getNumber() << " doesn't exist in the database" << std::endl;
        return;
    }

    std::cout << vehicle->getRegistration().getNumber() << " " << vehicle->getDescription();
    if (vehicle->isOwned())
    {
        std::cout << " " << vehicle->getOwner()->getId();
    }
    std::cout << std::endl;
}

void DataBase::removeVehicle(const Registration &registration)
{
    Vehicle *vehicle = findVehicle(registration);

    const size_t size = this->vehicles.size();

    if (vehicle == nullptr)
    {
        std::cout << "Vehicle with registration " << registration.getNumber() << " doesn't exist in the database" << std::endl;
        return;
    }

    if (vehicle->isOwned())
    {
        releaseVehicleFromPerson(vehicle->getOwner()->getId(), vehicle->getRegistration());
    }
    for (int i = 0; i < size; i++)
    {
        if (this->vehicles[i] == vehicle)
        {
            this->vehicles[i] = nullptr;
            this->vehicles.erase(this->vehicles.begin() + i);
            std::cout << "Vehicle with registration " << registration.getNumber() << " was successfully removed from the database." << std::endl;
            return;
        }
    }
}
void DataBase::removePerson(const unsigned id)
{
    Person *person = findPerson(id);

    const size_t size = this->people.size();

    if (person == nullptr)
    {
        std::cout << "Person with id " << id << " doesn't exist in the database" << std::endl;
        return;
    }
    if (person->cntOfVehicles())
    {
        person->removeAllVehicles();
    }
    for (int i = 0; i < size; i++)
    {
        if (this->people[i] == person)
        {
            this->people[i] = nullptr;
            this->people.erase(this->people.begin() + i);
            std::cout << "Person with id " << id << " was successfully removed from the database." << std::endl;
            return;
        }
    }
}

const Vehicle * DataBase::getVehicle(const Registration & reg)
{
    return this->findVehicle(reg);
}

const Person * DataBase::getPerson(const unsigned id)
{
    return this->findPerson(id);
}

std::vector<Registration> DataBase::getAllVehicleRegistrations() const
{
    std::vector<Registration> result;
    result.reserve(this->vehicles.size());
    for (int i = 0; i < this->vehicles.size(); i++)
    {
        result.push_back(this->vehicles[i]->getRegistration());
    }
    return result;
}

std::vector<unsigned int> DataBase::getAllPeopleIds() const
{
    std::vector<unsigned int> result(this->people.size());
    for (int i = 0; i < result.size(); i++)
    {
        result[i] = this->people[i]->getId();
    }
    return result;
}
