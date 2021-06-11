#include "Organizer.hpp"

Organizer::Organizer()
{
}

Organizer& Organizer::getInstance() 
{
    static Organizer instance;
    return instance;
}

void Organizer::addVehicle(std::string registration, std::string description) 
{
    Registration reg(registration); 
    for(std::size_t i = 0; i<vehicles.size(); ++i) 
    {
        if(vehicles[i].getReg() == registration) 
        {
            throw std::runtime_error("A vehicle with that registration already exists.");
        }
    }
    Vehicle temp(reg, description);
    vehicles.push_back(temp);
    if(vehicles.back().getReg() != temp.getReg())  
    {
        throw std::runtime_error("Memory error. Nothing was added.");
    }
}

void Organizer::addPerson(std::string name, unsigned int id)   
{
    if(id > 0) //0 is not a valid ID
    {
        for(std::size_t i = 0; i<people.size(); ++i) 
        {
            if(people[i].getId() == id) 
            {
                throw std::runtime_error("A person with that ID already exists.");
            }
        }
        Person temp(name, id);
        people.push_back(temp);
    }
    else
    {
        throw std::runtime_error("Invalid ID.");
    }
}

void Organizer::acquire(unsigned int id, std::string registration)
{
    std::size_t p = 0;
    bool flagP = 0;

    std::size_t v = 0;
    bool flagV = 0;

    while(p < people.size() && !flagP)
    {
        if(people[p].getId() == id)
        {
            flagP = 1;
        }
        if(!flagP)
        {
            ++p;
        }
    }
    while(v < vehicles.size() && !flagV)
    {
        if(vehicles[v].getReg() == registration)
        {
            flagV = 1;
        }
        if(!flagV)
        {
            ++v;
        }
    }
    if(!flagP && !flagV)
    {
        throw std::runtime_error("There are no such vehicle and person.");
    }
    if(!flagP)
    {
        throw std::runtime_error("This person does not exist.");
    }
    if(!flagV)
    {
        throw std::runtime_error("This vehicle does not exist.");
    }

    if(vehicles[v].getOwnerId())
    {
        release(vehicles[v].getOwnerId(), registration);
    }

    vehicles[v].addOwner(id);
    people[p].addVehicle(vehicles[v]);
}


void Organizer::release(unsigned int id, std::string registration)
{
    bool flag = 0;
    for(std::size_t i = 0; i<people.size(); ++i)
    {
        if(people[i].getId() == id)
        {
            if(people[i].releaseVehicle(registration))
            {
                for(std::size_t j = 0; j<vehicles.size(); ++j)
                {
                    if(vehicles[j].getReg() == registration)
                    {
                        vehicles[j].removeOwner();
                        flag = 1;
                        break;
                    }
                }
            }
            else
            {
                throw std::runtime_error("This person does not own this vehicle.");
            }
        }
    }
    if(!flag)
    {
        throw std::runtime_error("This person does not exist.");
    }
}

void Organizer::remove(unsigned int id)
{
    bool flag = 0;
    for(std::size_t i = 0; i<people.size(); ++i)
    {
        if(people[i].getId() == id)
        {
            for(std::size_t j = 0; j<people[i].numberOfVehicles(); ++j)
            {
                release(id, people[i].getVehicle(j)->getReg());
            }
            people.erase(people.begin()+i);
            flag = 1;
            break;
        }
    }
    if(!flag)
    {
        throw std::runtime_error("This person does not exist.");
    }
}

void Organizer::remove(std::string registration)
{
    bool flag = 0;
    for(std::size_t i = 0; i<vehicles.size(); ++i)
    {
        if(vehicles[i].getReg() == registration)
        {
            if(vehicles[i].getOwnerId())
            {
                release(vehicles[i].getOwnerId(), registration);
            }
            
            vehicles.erase(vehicles.begin() + i);
            flag = 1;
            break;
        }
    }
    if(!flag)
    {
        throw std::runtime_error("This vehicle does not exist.");
    }
}

unsigned Organizer::getPersonId(std::size_t pos) const
{
    if(pos<people.size())
    {
        return people[pos].getId();
    }
    else
    {
        throw std::out_of_range("Out of range");
    }
}

std::string Organizer::getVehicleReg(std::size_t pos) const
{
    if(pos<vehicles.size())
    {
        return vehicles[pos].getReg();
    }
    else
    {
        throw std::out_of_range("Out of range");
    }
}

Person* Organizer::getPerson(unsigned id)
{
    for(std::size_t i = 0; i<people.size(); ++i) 
    {
        if(people[i].getId() == id) //could throw
        {
            return &people[i];
        }
    }
    throw std::runtime_error("This person does not exist.");
}

Vehicle Organizer::getVehicle(std::string registration)
{
    for(std::size_t i = 0; i<vehicles.size(); ++i) 
    {
        if(vehicles[i].getReg() == registration) //could throw
        {
            return vehicles[i];
        }
    }
    throw std::runtime_error("This vehicle does not exist.");
}
