#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

class Vehicle
{
public:
    Vehicle(const Registration &reg, const char *str_des, const Person &per);
    Vehicle();
    ~Vehicle();

    void setVehicleRegistration(const char *str);
    void setVehicleDescription(const char *str);
    void setOwner(Person *rhs);
    const char *getVehicleRegistration() const;
    void printVehicle() const;
    void printVehicleSmallInfo() const;
    unsigned int getOwnerID() const;

private:
    Registration carnumber;
    std::string description;
    Person *owner;
};

Vehicle::Vehicle(const Registration &reg, const char *str_des, const Person &per)
{

}

Vehicle::Vehicle()
{
    owner=nullptr;
    description="";
}

Vehicle::~Vehicle()
{

}

void Vehicle::setVehicleRegistration(const char *str)
{
    carnumber.setRegistration(str);
}

void Vehicle::setVehicleDescription(const char *str)
{
    description=convertToString(str, strsize(str));
}

void Vehicle::printVehicle() const
{
    carnumber.printRegNumber();
    std::cout<<"Description: "<<description<<std::endl;

    if(owner != nullptr)
    {
        (*owner).printPerson();
    }
    else
    {
        std::cout<<"This vehicle has no owner!"<<std::endl;
    }
}

void Vehicle::printVehicleSmallInfo() const
{
    carnumber.printRegNumber();
    std::cout<<"Description: "<<description<<std::endl;
}

const char *Vehicle::getVehicleRegistration() const
{
    return carnumber.getRegNumber();
}

void Vehicle::setOwner(Person *rhs)
{
    this->owner=rhs;
}

unsigned int Vehicle::getOwnerID() const
{
    return (*owner).getID();
}
#endif // VEHICLE_H_INCLUDED
