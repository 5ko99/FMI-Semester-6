#include "Vehicle.hpp"
#include "Controller.hpp"

Vehicle::Vehicle(const Registration& reg, const std::string& desc): reg(reg), desc(desc){}

bool Vehicle::operator==(const Vehicle& other)
{
    return reg == other.reg;
}

Registration Vehicle::getRegistration() const
{
    return reg;
}

const std::string Vehicle::getDescription() const
{
    return desc;
}

Person* Vehicle::getOwner()
{
    // return Controller::getInstance().findPersonByVehicle(reg);
    return owner;
}

void Vehicle::setOwner(Person* p)
{
    owner = p;
}

std::ostream& operator<<(std::ostream& out, Vehicle& v)
{
    out << "registration: " << v.reg << "; description: " << v.desc << ";";

    Person* owner = v.getOwner();

    if(owner)
    {
        out << " owner: " << owner->getName() << ";";
    }

    return out;
}
