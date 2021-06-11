#include "person.h"

Person::Person()
    :id(0)
{}

Person::Person(const std::string& name, unsigned int id)
{
    this->name = name;
    this->id = id;
}

unsigned int Person::getId() const
{
    return id;
}

std::vector<Vehicle*>& Person::getVehicles()
{
    return vehicles;
}

void Person::releaseVehicle(const Registration& registrationNumber)
{
    int index = -1;
    for (std::size_t i = 0; i < vehicles.size(); ++i)
    {
        if (vehicles[i]->getRegistrationNumber() == registrationNumber)
            index = i;
    }
    if (index >= 0)
        vehicles.erase(vehicles.begin() + index);
}

void Person::buyVehicle(Vehicle& vehicle)
{
    vehicles.push_back(&vehicle);
}

void Person::setId(unsigned int id)
{
    this->id = id;
}

void Person::showVehicles()const
{
    if (vehicles.empty())
        std::cout << "This person has no vehicles!" << std::endl;
    else
    {
        std::cout << "The vehicles of person are: " << std::endl;
        for (Vehicle* v : vehicles)
        {
            std::cout << (*v);
        }
    }
}

std::ostream& operator <<(std::ostream& out, const Person& p)
{
    out << p.name << " " << p.id;
    /*for (Vehicle* v : p.vehicles)
    {
        out << v->getRegistrationNumber() << " ";
    }*/
    out << std::endl;
    return out;
}

std::istream& operator >>(std::istream& in, Person& p)
{
    in >> p.name >> p.id;
    /*for (Vehicle* v : p.vehicles)
    {
        Registration registrationNumber = v->getRegistrationNumber(); 
        in >> registrationNumber;
    }*/
    return in;
}
