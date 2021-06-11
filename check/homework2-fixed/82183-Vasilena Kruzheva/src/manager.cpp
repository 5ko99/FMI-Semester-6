#include "../include/manager.hpp"
#include <cstring>
#include <fstream>

using std::fstream;


void Manager::validateIDIndex(int index)
{
    if(index < 0){
        throw std::invalid_argument("Invalid ID!");
    }
}

bool Manager::takePermission(const char* message)
{
    char result;
    cout<< message << " Are you sure you want to continue? y/n:";
    cin>>result;

    if(result != 'y'){
        cout<<"Remove was canceled!\n";
        return false;
    }

    return true;
}

unsigned long Manager::convertToULong(const char* id)
{
    int temp = strlen(id);

    try{
        temp = std::stoul(id);
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument("Invalid ID!");
    }

    return temp;
}

int Manager::findPerson(unsigned int personID)
{
    for (size_t i = 0; i < people.size(); i++)
    {
        if(people[i].getID() == personID)
        {
            return i;
        }
    }
    
    return -1;
}

int Manager::findVehicle(const char* reg)
{
    for (size_t i = 0; i < vehicles.size(); i++)
    {
        if(strcmp(vehicles[i].getRegistration(), reg) == 0)
        {
            return i;
        }
    }
    
    return -1;
}

void Manager::addVehicle(const char* reg, string description)
{
    if(findVehicle(reg) == -1)
    {
        vehicles.push_back(Vehicle(reg, description));
    }
    else{
        throw std::invalid_argument("Vehicle with the given registration already exists!");
    }
}

void Manager::addPerson(string name, unsigned int ID)
{
    if(findPerson(ID) == -1)
    {
        people.push_back(Person(name, ID));
    }
    else{
        throw std::invalid_argument("Person with the given ID already exists!");
    }
}

void Manager::aquire(unsigned int personID, const char* reg)
{
    int indexP = findPerson(personID);
    int indexV = findVehicle(reg);

    if(indexP < 0 || indexV < 0){
        throw std::invalid_argument("Invalid ID!");
    }
    people[indexP].addVehicle(&vehicles[indexV]);
    //vehicles[indexV].setOwner(&people[indexP]);
}

void Manager::release(unsigned int personID, const char* reg)
{
    int indexP = findPerson(personID);
    int indexV = findVehicle(reg);

    if(indexP < 0 || indexV < 0){
        throw std::invalid_argument("Invalid ID!");
    }
    //vehicles[indexV].release();
    people[indexP].removeVehicle(&vehicles[indexV]);
}

void Manager::removePerson(unsigned int ID)
{
    int index = findPerson(ID);
    
    if(index < 0){
        throw std::invalid_argument("Invalid ID. Person was not found!");
    }

    if(people[index].vehiclesCount() > 0 && !takePermission("The person you want to remove owns vehicles.")){
        return;
    }

    people[index].freeVehicles();
    people.erase(people.begin() + index);
}

void Manager::removeVehicle(const char* reg)
{
    int index = findVehicle(reg);

    if(index < 0){
        throw std::invalid_argument("Invalid ID. Vehicle was not found!");
    }

    if(vehicles[index].hasOwner() > 0 && !takePermission("The vehicle you want to remove has owner.")){
        return;
    }

    vehicles[index].release();
    vehicles.erase(vehicles.begin() + index);
}

void Manager::remove(const char* id)
{
    if(Registration::validate(id))
    {
        removeVehicle(id);
    }
    else
    {
        removePerson(convertToULong(id));
    }
    
}

void Manager::save(const char* path)
{
    fstream out(path, std::ios::out | std::ios::trunc);
    if(!out.is_open()){
        out.clear();
        out.close();
        throw std::invalid_argument("Invalid file path!");
    }

    for (size_t i = 0; i < vehicles.size(); i++)
    {
        out << "vehicle " << vehicles[i].getRegistration() << " \"" << vehicles[i].getDescription() << "\""<< endl;
    }

    for (size_t i = 0; i < people.size(); i++)
    {
        out << "person \"" << people[i].getName() << "\" " << people[i].getID() << endl;

        for (size_t j = 0; j < people[i].vehiclesCount(); j++)
        {
            out<< "acquire " << people[i].getID() << " " << people[i].getVehicleID(j) << endl;
        }
    }
    out.close();
}

void Manager::show(const char* object)
{
    if(strcmp(object, "PEOPLE") == 0){
        for (size_t i = 0; i < people.size(); i++)
        {
            cout << i+1 <<". "<< people[i].getName() << ", " << people[i].getID() << endl;
        }
    }
    else if(strcmp(object, "VEHICLES") == 0){
        for (size_t i = 0; i < vehicles.size(); i++)
        {
            cout << i+1 <<". " << vehicles[i].getRegistration() << ", "  << vehicles[i].getDescription() << endl;
        }
    }
    else{
        int index;
        if(Registration::validate(object))
        {
            index = findVehicle(object);
            if(index < 0)
            {
                throw std::invalid_argument("Invalid registration number!");
            }
            cout << vehicles[index].getRegistration() << ", "  
                 << vehicles[index].getDescription();
            if(vehicles[index].hasOwner())
            {
                cout <<  ", " << "owner: " << vehicles[index].getOwner()->getID();
            }
            cout<<endl;
        }
        else{
            index = findPerson(convertToULong(object));
            if(index < 0){
                throw std::invalid_argument("Invalid ID!");
            }

            cout << people[index].getName() << ", " << people[index].getID() << endl;
            for (size_t i = 0; i < people[index].vehiclesCount(); i++)
            {
                cout << i + 1 <<". Vehicle id: " << people[index].getVehicleID(i) << ", " <<people[index].getVehicleDescription(i)<< endl;
            }
            
        }
    }
}

unsigned int Manager::getVehiclesCount()
{
    return vehicles.size();
}

unsigned int Manager::getPeopleCount()
{
    return people.size();
}
