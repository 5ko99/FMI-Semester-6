#include "system.h"

System::System()
{}

void System::addVehicle(const Vehicle& vehicle)
{
    if (getVehicleById(vehicle.getRegistrationNumber()) != -1)
    {
        std::cout << "This vehicle has already been registered!" << std::endl;
        return;
    }
    vehicles.push_back(vehicle);
}

void System::addPerson(const Person& person)
{
    if (getPersonById(person.getId()) != -1)
    {
        std::cout << "There is already an owner with this id!" << std::endl;
        return;
    }
    owners.push_back(person);
}

void System::setOwner(Vehicle& vehicle, Person& owner)
{
    Person* currentOwner = vehicle.getOwner();
    if (currentOwner != nullptr)
        currentOwner->releaseVehicle(vehicle.getRegistrationNumber());

    vehicle.setOwner(&owner);
    owner.buyVehicle(vehicle);
}

void System::setFile(const std::string& filePath)
{
    this->filePath = filePath;
}

void System::removePersonById(unsigned int id)
{
    int foundPerson = getPersonById(id);
    if (foundPerson == -1)
        throw std::invalid_argument("There is no owner with this id!");

    std::vector<Vehicle*>& personVehicles = owners[foundPerson].getVehicles();
    if (!personVehicles.empty())
    {
        std::cout << "This person has cars. Would you like to remove it!" << std::endl;
        char answer;
        std::cin >> answer;
        while(true)
        {
            if (answer == 'y')
            {
                for (Vehicle* v :personVehicles)
                {
                    v->setOwner(nullptr);
                }
                std::cin.ignore();
                break;
            }
            else if (answer == 'n')
            {
                std::cout << "Removal canceled!" << std::endl;
                std::cin.ignore();
                return;
            }
            else
            {
                std::cout << "Type \'y\' or \'n\' to answer the question!" << std::endl;
                std::cin >> answer;
            }
        }
    }
    owners.erase(owners.begin() + foundPerson);
}

void System::removeVehicleById(const Registration& registrationNumber)
{
    int foundVehicle = getVehicleById(registrationNumber);
    if(foundVehicle == -1)
        throw std::invalid_argument("There is no owner with this id!");

    Person* vehicleOwner = vehicles[foundVehicle].getOwner();
    if (vehicleOwner != nullptr)
    {
        std::cout << "This vehicle has an owner. Would you like to remove it?" << std::endl;
        char answer;
        std::cin >> answer;
        while (true)
        {
            if (answer == 'y')
            {
                vehicleOwner->releaseVehicle(registrationNumber);
                std::cin.ignore();
                break;
            }
            else if (answer == 'n')
            {
                std::cout << "Removal canceled!" << std::endl;
                std::cin.ignore();
                return;
            }
            else
            {
                std::cout << "Type \'y\' or \'n\' to answer the question!" << std::endl;
				std::cin >> answer;
            }
        }
    }
    vehicles.erase(vehicles.begin() + foundVehicle);
}

void System::saveData()
{
    std::ofstream file(filePath, std::ios::out);
    if (!file)
    {
        std::cout << "Problems in openning the file " << filePath << std::endl;
        return;
    }
    for (size_t i = 0; i < owners.size(); ++i)
    {
        file << "Person " << owners[i];
    }
    for (size_t i = 0; i < vehicles.size(); ++i)
    {
        file << "Vehicle " << vehicles[i];
    }
    
    for (size_t i = 0; i < owners.size(); ++i)
    {
        std::vector<Vehicle*>& vehicles = owners[i].getVehicles();
        for (Vehicle* v : vehicles)
        {
            file << "Acquire " << owners[i].getId() << " " << v->getRegistrationNumber();
            file << std::endl;
        }
    }

    file.close();
}

void System::showOwners() const
{
    if (owners.empty())
        std::cout << "There are no people registered in the system!" << std::endl;
    else
    {
        std::cout << "People in the system are:" << std::endl;
        for (Person p : owners)
            std::cout << p;
    }
}

void System::showVehicles() const
{
    if (vehicles.empty())
        std::cout << "There are no vehicles registered in the system!" << std::endl;
    else
    {
        std::cout << "Vehicles in the system are:" << std::endl;
        for (Vehicle v : vehicles)
            std::cout << v;
    }
}

int System::getPersonById(unsigned int id) const
{
    for (size_t i = 0; i < owners.size(); ++i)
    {
        if (owners[i].getId() == id)
            return i;
    }
    return -1;
}

int System::getVehicleById(const Registration& registrationNumber) const
{
    for (size_t i = 0; i < vehicles.size(); ++i)
    {
        if (vehicles[i].getRegistrationNumber() == registrationNumber)
            return i;
    }
    return -1;
}

std::string System::getFile() const
{
    return filePath;
}

Person& System::personAt(size_t index)
{
	//!!! exception if index is out of range
    if (index < 0 || index >= owners.size())
        throw std::out_of_range("Index is not in the range!");
    return owners[index];
}

Vehicle& System::vehicleAt(size_t index)
{
	//!!! exception if index is out of range
    if (index < 0 || index >= vehicles.size())
        throw std::out_of_range("Index is not in the range!");
    return vehicles[index];
}
