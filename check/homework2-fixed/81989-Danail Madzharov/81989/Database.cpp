#include "Database.h"
#include <iostream>
#include <regex>
#include <fstream>

vector<Person *> Database::getPeople()
{
    return this->people;
}

vector<Vehicle *> Database::getCars()
{
    return this->cars;
};

void Database::addPerson(Person *person)
{
    if (doesPersonExistAlready(person->getId()))
    {
        cout << "A person with this ID already exists, adding unsuccessful" << endl;
        return;
    }
    peopleIds.insert(person->getId());
    people.push_back(person);
    cout << "A person with ID " << person->getId() << " has been added successfully" << endl;
}

void Database::addVehicle(Vehicle *vehicle)
{
    if (doesVehicleExistAlready(vehicle->getRegistrationNumber()->getRegNumber()))
    {
        cout << "A vehicle with this ID already exists, adding unsuccessful" << endl;
        return;
    }
    vehiclesRegistrations.insert(vehicle->getRegistrationNumber()->getRegNumber());
    cars.push_back(vehicle);
    cout << "A vehicle with reg. number " << vehicle->getRegistrationNumber()->getRegNumber() << " has been added successfully" << endl;
}

void Database::printAll()
{
    cout << endl
         << "Cars: " << endl;

    for (Vehicle *v : this->cars)
    {
        cout << v->getRegistrationNumber()->getRegNumber() << endl;
    }

    cout << endl
         << "Names: " << endl;

    for (Person *person : this->people)
    {
        cout << person->getName();
    }
}

bool Database::isPersonFound(Person *person)
{
    return peopleIds.count(person->getId());
}

bool Database::isCarFound(Vehicle *car)
{
    return vehiclesRegistrations.count(car->getRegistrationNumber()->getRegNumber());
}

void Database::setCarOwner(Person *person, Vehicle *car)
{
    if (!isPersonFound(person) || !isCarFound(car))
    {
        cout << "The person or car is not present in the database" << endl;
        return;
    }
    car->setOwner(person);
    person->addCar(car->getRegistrationNumber());
    cout << car->getRegistrationNumber()->getRegNumber() << " is now a car owned by " << person->getName();
}

void Database::removeCarOwner(Person *person, Vehicle *car)
{
    if (!isPersonFound(person) || !isCarFound(car))
    {
        cout << "The person or car is not present in the database" << endl;
        return;
    }
    if (car->getOwner() == person)
    {
        car->setOwner(nullptr);
        person->removeCar(car->getRegistrationNumber());
        cout << car->getRegistrationNumber()->getRegNumber() << " is no longer a car owned by " << person->getName();
    }
}

bool Database::validateRegNumber(string reg)
{
    regex r("[A-Z][A-Z][0-9][0-9][0-9][0-9][A-Z][A-Z]");
    regex r2("[A-Z][0-9][0-9][0-9][0-9][A-Z][A-Z]");
    return regex_match(reg, r) | regex_match(reg, r2);
}

bool Database::doesPersonExistAlready(unsigned int id)
{
    return this->peopleIds.count(id);
}

bool Database::doesVehicleExistAlready(string reg)
{
    return this->vehiclesRegistrations.count(reg);
}

Person *Database::getPersonById(unsigned int id)
{
    for (Person *current : this->people)
    {
        if (current->getId() == id)
        {
            return current;
        }
    }

    return nullptr;
}

Vehicle *Database::getVehicleByRegNumber(string regNumber)
{
    for (Vehicle *current : this->cars)
    {
        if (current->getRegistrationNumber()->getRegNumber() == regNumber)
        {
            return current;
        }
    }

    return nullptr;
}

void Database:: deleteCarFromDatabase(string regNumber)
{
    Vehicle *vehicle = this->getVehicleByRegNumber(regNumber);
    if (vehicle == nullptr)
    {
        return;
    }

    Person *owner = vehicle->getOwner();

    if (owner != nullptr)
    {
        std::cout << "This vehicle has an owner, are you sure you want to continue? Type y/n" << std::endl;
        std::string answer;
        do
        {
            std::cout << "choice: ";
            std::cin >> answer;
        } while (answer != "y" && answer != "n");

        if (answer == "y")
        {
            std::cout << std::endl;
            owner->removeCar(vehicle->getRegistrationNumber());
        }
        else
        {
            return;
        }
    }

    this->vehiclesRegistrations.erase(regNumber);
    int counter = 0;
    for (Vehicle *current : this->cars)
    {
        if (current == vehicle)
        {
            break;
        }
        ++counter;
    }
    this->cars.erase(this->cars.begin() + counter);
    delete vehicle;
}

void Database::deletePersonFromDatabase(unsigned int idNumber)
{
    Person *foundPerson = this->getPersonById(idNumber);

    if (foundPerson == nullptr)
    {
        return;
    }

    if (!foundPerson->getOwnedCars().empty())
    {
        std::cout << "This person has one or more vehicles, are you sure you want to continue? Type y/n" << std::endl;
        std::string answer;
        do
        {
            std::cout << "choice: ";
            std::cin >> answer;
        } while (answer != "y" && answer != "n");

        if (answer == "y")
        {

            for (Vehicle *current : this->cars)
            {
                if (current->getOwner() == foundPerson)
                {
                    current->setOwner(nullptr);
                }
            }
        }
        else
        {
            return;
        }
    }

    this->peopleIds.erase(idNumber);

    int counter = 0;
    for (Person *current : this->people)
    {
        if (current == foundPerson)
        {
            break;
        }
        ++counter;
    }
    this->people.erase(this->people.begin() + counter);
    delete foundPerson;
}

void Database::printAllPeople()
{
    for (Person *current : people)
    {
        cout << "Name: " << current->getName() << "; ID: " << current->getId() << endl;
    }
}

void Database::printAllVehicles()
{
    for (Vehicle *current : cars)
    {
        if (current->getOwner() == nullptr)
        {
            cout << "Owner: no owner; Reg. Number: " << current->getRegistrationNumber()->getRegNumber() << endl;
        }
        else
        {
            cout << "Owner: " << current->getOwner()->getName() << "; Reg. Number: " << current->getRegistrationNumber()->getRegNumber() << endl;
        }
    }
}

void Database::printVehicleByRegNumber(string regNumber)
{
    Vehicle *current = this->getVehicleByRegNumber(regNumber);

    if (current == nullptr)
    {
        cout << "Vehicle not found" << endl;
        return;
    }

    if (current->getOwner() == nullptr)
    {
        cout << "Owner: no owner; Reg. Number: " << current->getRegistrationNumber()->getRegNumber() << endl;
    }
    else
    {
        cout << "Owner: " << current->getOwner()->getName() << "; Reg. Number: " << current->getRegistrationNumber()->getRegNumber() << endl;
    }
}

void Database::printPersonById(unsigned int idNumber)
{
    Person *current = this->getPersonById(idNumber);

    if (current == nullptr)
    {
        cout << "Person not found" << endl;
        return;
    }

    cout << "Name: " << current->getName() << endl
         << "Cars: " << endl;
    int counter = 0;
    for (Registration *reg : current->getOwnedCars())
    {
        counter++;
        cout << counter << ". " << reg->getRegNumber() << endl;
    }
}

void Database::saveInformationToFile(string path) {
    std::ofstream file(path, ios::app);
    file<<"People:"<<endl<<endl;
    int counter = 1;
    for (Person* current : this->people)
    {
        file<<(counter++)<<". Name: "<<current->getName()<<"; ID: "<<current->getId()<<endl;
    }

    file<<endl<<"Vehicles:"<<endl<<endl;
    counter = 1;

    for (Vehicle* current: this->cars) {
        file<<(counter++)<<". Owner: "<<current->getOwner()->getName()<<"; Reg. number: "<<current->getRegistrationNumber()->getRegNumber()<<endl;
    }
    file<<"----------------------------------------"<<endl;
    file.close();
}

set<unsigned int> Database::getpeopleIds() {
    return this->peopleIds;
}

set<string> Database::getVehiclesRegistrations() {
    return this->vehiclesRegistrations;
}

Database::~Database() {
    for (Person* current : this->people) {
        delete current;
    }

    for(Vehicle* current : this->cars) {
        delete current->getRegistrationNumber();
        delete current;
    }
}
