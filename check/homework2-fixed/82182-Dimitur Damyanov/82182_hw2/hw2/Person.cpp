#include "Person.hpp"

Person::Person(std::string name,  unsigned int id)
{
    this->name = name;
    this->id = id;
}

const Vehicle& Person::addVehicle(Vehicle* v)
{
    vehicles.push_back(v);

    v->setOwner(this);

    return *(vehicles.back());
}

void Person::removeVehicle(Vehicle* const v)
{
    auto toRemove = std::find(vehicles.begin(), vehicles.end(), v);

    if(toRemove != vehicles.end())
    {
        vehicles.erase(toRemove);
        // v->setOwner(nullptr);
    }
}

void Person::removeVehicle(const Registration& r)
{
    for(auto it = vehicles.begin(); it != vehicles.end(); it++)
    {
        if((**it).getRegistration() == r)
        {
            vehicles.erase(it);
            // (*it)->setOwner(nullptr);
            break;
        }
    }
}

const std::string Person::getName() const
{
    return name;
}

std::ostream& operator<<(std::ostream& out, Person const& p)
{
    out << "id: " << p.id << "; name: " << p.name << ";";

    return out;
}

void Person::printVehicles() const
{
    for(auto it = vehicles.begin(); it != vehicles.end(); it++)
    {
        std::cout << "- " << (**it) << std::endl;
    }
}

unsigned int Person::getId() const
{
    return id;
}

bool Person::has(Registration& reg) const
{
    for (std::vector<Vehicle*>::const_iterator it = vehicles.begin(); it != vehicles.end(); it++)
    {
        if(reg == (*it)->getRegistration())
        {
            return true;
        }
    }

    return false;
}

void Person::clear()
{
    // for (std::vector<Vehicle*>::iterator it = vehicles.begin(); it != vehicles.end(); it++)
    // {
    //      (**it).setOwner(nullptr);
    // }

    vehicles.clear();
}

size_t Person::getVehiclesCount() const
{
    return vehicles.size();
}
