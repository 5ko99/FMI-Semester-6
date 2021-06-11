#include "Database.h"
using namespace std;

Person *Database::findById(const unsigned int &_id)
{
    for (auto ppl : people)
    {
        if (ppl->getId() == _id)
        {
            return ppl;
        }
    }
    return nullptr;
}

Vehicle *Database::findById(const string &_id)
{
    for (auto veh : allVehicles)
    {
        if (veh->getId() == _id)
        {
            return veh;
        }
    }
    return nullptr;
}

void Database::copy(vector<Vehicle *> _allVehicles, vector<Person *> _people)
{
    for (int i = 0; i < _allVehicles.size(); i++)
    {
        allVehicles.push_back(_allVehicles[i]->clone_veh());
    }

    for (int j = 0; j < _people.size(); j++)
    {
        people.push_back(_people[j]->clone_person());
    }
}

// Database::Database(vector<Vehicle *> _allVehicles, vector<Person *> _people)
// {
//     copy(_allVehicles, _people);
// }

// Database::Database(const Database &other)
// {
//     copy(other.allVehicles, other.people);
// }

bool Database::isStringNumber(string str)
{
    try
    {
        stoi(str);
    }
    catch (invalid_argument &e)
    {
        return false;
    }
    return true;
}

bool Database::validateRegNum(string regNumber)
{
    if (regNumber.length() < 7 || regNumber.length() > 8)
    {
        return false;
    }

    if (regNumber.length() == 7)
    {
        if (regNumber[0] >= 'A' && regNumber[0] <= 'Z')
        {
            for (int i = 1; i <= 4; i++)
            {
                if (regNumber[i] < '0' && regNumber[i] > '9')
                {
                    return false;
                }
            }
            if ((regNumber[5] <= 'A' && regNumber[5] >= 'Z') && (regNumber[6] <= 'A' && regNumber[6] >= 'Z'))
            {
                return false;
            }
        }
    }

    if (regNumber.length() == 8)
    {
        if ((regNumber[0] >= 'A' && regNumber[0] <= 'Z') && (regNumber[1] >= 'A' && regNumber[1] <= 'Z'))
        {
            for (int i = 2; i <= 5; i++)
            {
                if (regNumber[i] < '0' && regNumber[i] > '9')
                {
                    return false;
                }
            }
            if ((regNumber[6] <= 'A' && regNumber[6] >= 'Z') && (regNumber[7] <= 'A' && regNumber[7] >= 'Z'))
            {
                return false;
            }
        }
    }
    return true;
}

void Database::vehicle_command(const string registration, const string description)
{

    if (!validateRegNum(registration))
    {
        cout << "invalid reg numb\n";
        return;
    }
    Registration *newReg = new Registration(registration);
    for (auto veh : this->allVehicles)
    {
        if (veh->getRegistration()->getRegNum() == registration)
        {
            cout << "Adding was unsuccessfull, same vehicle already exists \n";
            return;
        }
    }
    allVehicles.push_back(new Vehicle(newReg, description));
}

void Database::person_command(const string _name, const unsigned int _id)
{
    for (auto per : this->people)
    {
        if (per->getId() == _id)
        {
            cout << "Adding was unsuccessfull, ID is taken\n";
            return;
        }
    }
    people.push_back(new Person(_name, _id));
}

void Database::acquire_command(const unsigned int &owner_id, const string &vehicle_id)
{
    if (!findById(owner_id) || !findById(vehicle_id))
    {
        cout << "Person or vehicle does not exist";
        return;
    }

    Person *foundPer = findById(owner_id);
    Vehicle *foundVeh = findById(vehicle_id);

    if (foundVeh->getOwner() != nullptr)
    {
        int counter = 0;
        for (auto veh : foundVeh->getOwner()->getOwnedVehicles())
        {
            if (veh == foundVeh)
            {
                break;
            }
            counter++;
        }

        foundVeh->getOwner()->getOwnedVehicles().erase(foundVeh->getOwner()->getOwnedVehicles().begin() + counter);
    }

    foundPer->addVehicle(findById(vehicle_id));
    foundVeh->setOwner(foundPer);
}

void Database::release_command(const unsigned int &owner_id, const string &vehicle_id)
{
    Person *foundPer = findById(owner_id);
    Vehicle *foundVeh = findById(vehicle_id);

    if (foundPer == nullptr || foundVeh == nullptr)
    {
        cout << "Person or vehicle does not exist";
        return;
    }

    if (foundVeh->getOwner() == foundPer)
    {
        int counter = 0;
        for (auto veh : foundVeh->getOwner()->getOwnedVehicles())
        {
            if (veh == foundVeh)
            {
                break;
            }
            counter++;
        }

        foundVeh->getOwner()->getOwnedVehicles().erase(foundVeh->getOwner()->getOwnedVehicles().begin() + counter);
        foundVeh->setOwner(nullptr);
    }
    else
    {
        cout << "This person is not an owner of " << foundVeh->getRegistration()->getRegNum() << " and cannot be removed\n";
        return;
    }
}

void Database::remove_command(string what)
{

    if (validateRegNum(what))
    {
        Vehicle *veh = findById(what);
        if (veh == nullptr)
        {
            return;
        }
        deleteVehicleFromDB(veh);
    }
    else if (isStringNumber(what))
    {
        int number = stoi(what);
        Person *foundPer = findById(number);
        if (foundPer == nullptr)
        {
            return;
        }
        deletePersonFromDB(foundPer);
    }
    else
    {
        cout << "Invalid argument" << endl;
    }
}

void Database::deletePersonFromDB(Person *person)
{
    for (auto veh : person->getOwnedVehicles())
    {
        veh->setOwner(nullptr);
    }

    int current = 0;

    for (auto per : this->people)
    {
        if (per == person)
        {
            break;
        }
        ++current;
    }

    this->people.erase(this->people.begin() + current);
    delete person;
}

void Database::deleteVehicleFromDB(Vehicle *vehicle)
{
    if (vehicle->getOwner() != nullptr)
    {
        int counter = 0;
        for (auto veh : vehicle->getOwner()->getOwnedVehicles())
        {
            if (veh == vehicle)
            {
                veh->setOwner(nullptr);
                break;
            }
            ++counter;
        }
    }

    int counter = 0;
    for(auto veh : this->allVehicles) {
        if (veh == vehicle) {
            break;
        }
        counter++;
    }

    this->allVehicles.erase((this->allVehicles.begin()) + counter);
    delete vehicle;
}
